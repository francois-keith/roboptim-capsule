// Copyright (C) 2012 by Antonio El Khoury, CNRS.
//
// This file is part of the roboptim-capsule.
//
// roboptim-capsule is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// roboptim-capsule is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with roboptim-capsule.  If not, see <http://www.gnu.org/licenses/>.


#ifndef ROBOPTIM_CAPSULE_UTIL_HH_
# define ROBOPTIM_CAPSULE_UTIL_HH_

# include <iostream>
# include <set>
# include <limits>

# include <boost/foreach.hpp>

# include <roboptim/capsule/config.hh>
# include <roboptim/capsule/fwd.hh>
# include <roboptim/capsule/types.hh>
# include <roboptim/capsule/qhull.hh>

namespace roboptim
{
  namespace capsule
  {

    /// Creates a convex hull from a set of points.
    ROBOPTIM_CAPSULE_DLLAPI
    polyhedron_t convexHullFromPoints (const std::vector<point_t>& points);

    /// \brief Structure containing Capsule data (start point, end point and
    // radius).
    struct ROBOPTIM_CAPSULE_DLLAPI Capsule
    {
      point_t P0, P1;
      value_type radius;

      Capsule ()
	: P0 (0., 0., 0.),
	  P1 (0., 0., 0.),
	  radius (0.)
      {}
    };

    /// \brief Compute the distance from point p to segment [a,b].
    ///
    /// \param p point.
    /// \param a start point of segment.
    /// \param b end point of segment.
    ///
    /// \return distance from p to the segment.
    ROBOPTIM_CAPSULE_DLLAPI
    value_type distancePointToSegment (const point_t& p,
                                       const point_t& a,
                                       const point_t& b);

    /// \brief Compute the project of point p on segment [a,b].
    ///
    /// \param p point.
    /// \param a start point of segment.
    /// \param b end point of segment.
    ///
    /// \return projection of p on [a,b].
    ROBOPTIM_CAPSULE_DLLAPI
    point_t projectionOnSegment (const point_t& p,
                                 const point_t& a,
                                 const point_t& b);

    /// \brief Distance from a point to a line described as a point and a
    // direction.
    ROBOPTIM_CAPSULE_DLLAPI
    value_type distancePointToLine (const point_t& point,
                                    const point_t& linePoint,
                                    const vector3_t& dir);

    /// \brief Compute the covariance matrix of a set of points.
    ROBOPTIM_CAPSULE_DLLAPI
    Eigen::Matrix3d covarianceMatrix (const std::vector<point_t>& points);

    // Returns indices imin and imax into pt[] array of the least and
    // most, respectively, distant points along the direction dir
    ROBOPTIM_CAPSULE_DLLAPI
    void extremePointsAlongDirection (vector3_t dir,
                                      const std::vector<point_t>& points,
                                      int& imin, int& imax);

    /// Computes a capsule from a set of points.
    /// The algorithm currently used relies on the search of the largest spread
    /// direction (PCA).
    /// TODO: Optimize computation speed.
    /// Spheres on both ends do not contain any point yet, cylinder length
    /// could be shortened to have a better fit.
    ROBOPTIM_CAPSULE_DLLAPI
    Capsule capsuleFromPoints (const std::vector<point_t>& points);

    /// \brief Convert Capsule parameters to RobOptim solver
    /// parameters vector.
    ///
    /// \param endPoint1 capsule axis first end point
    /// \param endPoint2 capsule axis second end point
    /// \param radius capsule radius
    /// \return dst parameters vector containing, in this
    /// order, the capsule axis first end point coordinates, the
    /// capsule axis second end point coordinates and the radius.
    ROBOPTIM_CAPSULE_DLLAPI
    void convertCapsuleToSolverParam (argument_ref dst,
				      const point_t& endPoint1,
				      const point_t& endPoint2,
				      const value_type& radius);

    /// \brief Convert RobOptim solver parameters vector to Capsule
    /// parameters.
    ///
    /// \param src parameters vector containing, in this
    /// order, the capsule axis first end point coordinates, the
    /// capsule axis second end point coordinates and the radius.
    /// \return endPoint1 capsule axis first end point
    /// \return endPoint2 capsule axis second end point
    /// \return radius capsule radius
    ROBOPTIM_CAPSULE_DLLAPI
    void convertSolverParamToCapsule (point_t& endPoint1,
				      point_t& endPoint2,
				      value_type& radius,
				      const argument_t src);

    /// \brief Convert a polyhedron vector to a single polyhedron.
    ///
    /// Result polyhedron is the union of all polyhedrons.
    ///
    /// \param polyhedrons polyhedron vector containing all
    /// polyhedrons.
    ///
    /// \return polyhedron union polyhedron
    ROBOPTIM_CAPSULE_DLLAPI
    void
    convertPolyhedronVectorToPolyhedron (polyhedron_t& polyhedron,
					 const polyhedrons_t& polyhedrons);

    /// \brief Compute bounding capsule of a vector of polyhedrons.
    ///
    /// Compute axis of capsule segment using least-squares fit. Radius
    /// is maximum distance from points to axis. Hemispherical caps are
    /// chosen as close together as possible.
    ///
    /// \param polyhedrons vector of polyhedrons that contain the
    /// points
    /// \return endPoint1 bounding capsule segment first end point
    /// \return endPoint2 bounding capsule segment second end point
    /// \return radius bounding capsule radius
    ROBOPTIM_CAPSULE_DLLAPI void
    computeBoundingCapsulePolyhedron (const polyhedrons_t& polyhedrons,
				      point_t& endPoint1,
				      point_t& endPoint2,
				      value_type& radius);

    /// \brief Compute the convex polyhedron over a vector of
    /// polyhedrons.
    ///
    /// Compute the polygon representing the convex hull of the union
    /// of all polyhedrons in a vector, and store it in a one-element
    /// vector.
    ///
    /// \param polyhedrons vector of polyhedrons that contain the
    /// points
    ///
    /// \return convexPolyhedron vector of polyhedrons containing one
    /// element, i.e. the convex hull.
    ROBOPTIM_CAPSULE_DLLAPI void
    computeConvexPolyhedron (const polyhedrons_t& polyhedrons,
			     polyhedrons_t& convexPolyhedrons);

  } // end of namespace capsule.
} // end of namespace roboptim.

#endif //! ROBOPTIM_CAPSULE_UTIL_HH_

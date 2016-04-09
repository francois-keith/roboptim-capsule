// Copyright (C) 2012 by Antonio El Khoury, CNRS.
//
// This file is part of the roboptim-capsule.
//
// roboptim-capsule is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// roboptim-capsule is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with roboptim-capsule.  If not, see
// <http://www.gnu.org/licenses/>.

/**
 * \brief Declaration of DistanceSegmentPoint class that computes
 * the distance between a segment and a point.
 */

#ifndef ROBOPTIM_CAPSULE_DISTANCE_CAPSULE_POINT_HH
# define ROBOPTIM_CAPSULE_DISTANCE_CAPSULE_POINT_HH

# include <roboptim/core/differentiable-function.hh>

# include <roboptim/capsule/config.hh>
# include <roboptim/capsule/types.hh>

namespace roboptim
{
  namespace capsule
  {
    /// \brief Distance to point RobOptim function.
    class ROBOPTIM_CAPSULE_DLLAPI DistanceCapsulePoint
      : public roboptim::DifferentiableFunction
    {
    public:
      /// \brief Constructor.
      ///
      /// \param point point that will be used in computing distance
      /// between the capsule and the point.
      DistanceCapsulePoint (const point_t& point,
			    std::string name
			    = "distance to point");

      ~DistanceCapsulePoint ();

      /// \brief Get point attribute.
      virtual const point_t& point () const;

    protected:
      /// \brief Computes the distance from capsule to a point.
      ///
      /// If the result is negative, the point is inside the capsule,
      /// otherwise it is outside the capsule.
      ///
      /// \param argument vector containing the capsule parameters. It
      /// contains in this order: the segment first end point
      /// coordinates, the segment second end point coordinates, the
      /// capsule radius.
      virtual void
      impl_compute (result_ref result,
		    const_argument_ref argument) const;

      /// \brief Compute of the distance gradient with respect to the
      /// capsule parameters.
      ///
      /// \param argument vector containing the capsule parameters. It
      /// contains in this order: the segment first end point
      /// coordinates, the segment second end point coordinates, the
      /// capsule radius.
      virtual void
      impl_gradient (gradient_ref gradient,
		     const_argument_ref argument,
		     size_type functionId = 0) const;

    private:
      /// \brief Point attribute.
      point_t point_;
    };

  } // end of namespace capsule.
} // end of namespace roboptim.

#endif //! ROBOPTIM_CAPSULE_DISTANCE_CAPSULE_POINT_HH

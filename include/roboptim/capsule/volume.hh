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
 * \brief Declaration of Volume class that computes the volume and
 * gradient of a capsule.
 */

#ifndef ROBOPTIM_CAPSULE_VOLUME_HH
# define ROBOPTIM_CAPSULE_VOLUME_HH

# include <roboptim/core/differentiable-function.hh>

# include "roboptim/capsule/config.hh"
# include "roboptim/capsule/types.hh"

namespace roboptim
{
  namespace capsule
  {
    /// \brief Capsule volume function.
    ///
    /// This class computes the volume of a capsule defined by a
    /// segment and a radius.
    class ROBOPTIM_CAPSULE_DLLAPI Volume
      : public roboptim::DifferentiableFunction
    {
    public:
      /// \brief Constructor.
      Volume (std::string name = "capsule volume");

      ~Volume ();

    protected:
      /// \brief Compute the volume of the capsule.
      ///
      /// \param argument vector containing the capsule parameters. It
      /// contains in this order: the segment first end point
      /// coordinates, the segment second end point coordinates, the
      /// capsule radius.
      virtual void
      impl_compute (result_ref result,
		    const_argument_ref argument) const;

      /// \brief Compute gradient of the capsule volume with respect
      /// to the argument vector.
      virtual void
      impl_gradient (gradient_ref gradient,
		     const_argument_ref argument,
		     size_type functionId = 0) const;
    };

  } // end of namespace capsule.
} // end of namespace roboptim.

#endif //! ROBOPTIM_CAPSULE_VOLUME_HH

/*
 * Copyright (C) 2010-2022 The ESPResSo project
 * Copyright (C) 2002,2003,2004,2005,2006,2007,2008,2009,2010
 *   Max-Planck-Institute for Polymer Research, Theory Group
 *
 * This file is part of ESPResSo.
 *
 * ESPResSo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESPResSo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/** \file
 *  RATTLE algorithm (@cite andersen83a).
 *
 *  For more information see \ref rattle.cpp.
 */

#include "config/config.hpp"

#ifdef BOND_CONSTRAINT

#include "BoxGeometry.hpp"
#include "bonded_interactions/bonded_interaction_data.hpp"
#include "cell_system/CellStructure.hpp"

/**
 * @brief Transfer the current particle positions from @ref Particle::pos
 * to @ref Particle::pos_last_time_step.
 */
void save_old_position(ParticleRange const &particles,
                       ParticleRange const &ghost_particles);

/**
 * @brief Propagate velocity and position while using SHAKE algorithm for bond
 * constraint.
 */
void correct_position_shake(CellStructure &cs, BoxGeometry const &box_geo,
                            BondedInteractionsMap const &bonded_ias);

/**
 * @brief Correction of current velocities using RATTLE algorithm.
 */
void correct_velocity_shake(CellStructure &cs, BoxGeometry const &box_geo,
                            BondedInteractionsMap const &bonded_ias);

#endif

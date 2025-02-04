/*
 * Copyright (C) 2022 The ESPResSo project
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

#include "ParticleHandle.hpp"

#include "script_interface/ScriptInterface.hpp"
#include "script_interface/auto_parameters/AutoParameters.hpp"
#include "script_interface/cell_system/CellSystem.hpp"
#include "script_interface/interactions/BondedInteractions.hpp"

#include "core/system/System.hpp"

#include <memory>
#include <string>
#include <vector>

namespace ScriptInterface {
namespace Particles {

class ParticleSlice : public AutoParameters<ParticleSlice> {
  std::vector<int> m_id_selection;
  int m_chunk_size;
  std::weak_ptr<CellSystem::CellSystem> m_cell_structure;
  std::weak_ptr<Interactions::BondedInteractions> m_bonded_ias;
  std::weak_ptr<::System::System> m_system;

public:
  ParticleSlice() {
    add_parameters({
        {"chunk_size", AutoParameter::read_only,
         [this]() { return m_chunk_size; }},
        {"id_selection", AutoParameter::read_only,
         [this]() { return m_id_selection; }},
    });
  }

  void do_construct(VariantMap const &params) override;

  Variant do_call_method(std::string const &name,
                         VariantMap const &params) override;

  void attach(std::weak_ptr<::System::System> system) {
    assert(m_system.expired());
    m_system = system;
  }
};

} // namespace Particles
} // namespace ScriptInterface

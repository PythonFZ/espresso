/*
 * Copyright (C) 2010-2022 The ESPResSo project
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

/**
 * @file
 * @brief ScriptInterface implementations for the
 *        various couplings provided.
 *
 * These are separated from the Constraints because
 * they can be reused together with the couplings themselves.
 */

#include "core/field_coupling/couplings/Charge.hpp"
#include "core/field_coupling/couplings/Direct.hpp"
#include "core/field_coupling/couplings/Mass.hpp"
#include "core/field_coupling/couplings/Scaled.hpp"
#include "core/field_coupling/couplings/Viscous.hpp"

#include "script_interface/ScriptInterface.hpp"

#include <unordered_map>
#include <vector>

namespace ScriptInterface {
namespace Constraints {
namespace detail {
using namespace ::FieldCoupling::Coupling;

/**
 * Default version for parameterless couplings.
 */
template <typename Coupling> struct coupling_parameters_impl {
  static Coupling make(const VariantMap &) { return Coupling{}; }
  template <typename This>
  static std::vector<AutoParameter> params(const This &) {
    return {};
  }
};

template <> struct coupling_parameters_impl<Viscous> {
  template <typename This>
  static std::vector<AutoParameter> params(const This &this_) {
    return {{
        "gamma",
        AutoParameter::read_only,
        [this_]() { return this_().gamma(); },
    }};
  }
};

template <> struct coupling_parameters_impl<Scaled> {
  template <typename This>
  static std::vector<AutoParameter> params(const This &this_) {
    return {{
                "default_scale",
                AutoParameter::read_only,
                [this_]() { return this_().default_scale(); },
            },
            {"particle_scales", AutoParameter::read_only, [this_]() {
               return make_unordered_map_of_variants(this_().particle_scales());
             }}};
  }
};

template <typename Coupling, typename This>
static std::vector<AutoParameter> coupling_parameters(const This &this_) {
  return coupling_parameters_impl<Coupling>::params(this_);
}

template <typename T> T make_coupling(const VariantMap &) { return T{}; }
template <> inline Viscous make_coupling<Viscous>(const VariantMap &params) {
  return Viscous{get_value<double>(params, "gamma")};
}

template <> inline Scaled make_coupling<Scaled>(const VariantMap &params) {
  return Scaled{get_value_or<std::unordered_map<int, double>>(
                    params, "particle_scales", {}),
                get_value<double>(params, "default_scale")};
}
} // namespace detail
} // namespace Constraints
} // namespace ScriptInterface

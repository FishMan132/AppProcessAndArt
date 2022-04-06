/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_COMPILER_OPTIMIZING_INSTRUCTION_SIMPLIFIER_ARM_H_
#define ART_COMPILER_OPTIMIZING_INSTRUCTION_SIMPLIFIER_ARM_H_

#include "nodes.h"
#include "optimization.h"

namespace art {
namespace arm {

class InstructionSimplifierArmVisitor : public HGraphVisitor {
 public:
  InstructionSimplifierArmVisitor(HGraph* graph, OptimizingCompilerStats* stats)
      : HGraphVisitor(graph), stats_(stats) {}

 private:
  void RecordSimplification() {
    if (stats_ != nullptr) {
      stats_->RecordStat(kInstructionSimplificationsArch);
    }
  }

  void VisitMul(HMul* instruction) OVERRIDE;
  void VisitOr(HOr* instruction) OVERRIDE;
  void VisitAnd(HAnd* instruction) OVERRIDE;

  OptimizingCompilerStats* stats_;
};


class InstructionSimplifierArm : public HOptimization {
 public:
  InstructionSimplifierArm(HGraph* graph, OptimizingCompilerStats* stats)
    : HOptimization(graph, "instruction_simplifier_arm", stats) {}

  void Run() OVERRIDE {
    InstructionSimplifierArmVisitor visitor(graph_, stats_);
    visitor.VisitReversePostOrder();
  }
};

}  // namespace arm
}  // namespace art

#endif  // ART_COMPILER_OPTIMIZING_INSTRUCTION_SIMPLIFIER_ARM_H_

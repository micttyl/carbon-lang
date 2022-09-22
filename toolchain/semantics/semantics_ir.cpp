// Part of the Carbon Language project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "toolchain/semantics/semantics_ir.h"

#include "common/check.h"
#include "toolchain/semantics/node_kind.h"
#include "toolchain/semantics/node_ref.h"
#include "toolchain/semantics/node_store.h"
#include "toolchain/semantics/nodes/binary_operator.h"
#include "toolchain/semantics/nodes/function.h"
#include "toolchain/semantics/nodes/integer_literal.h"
#include "toolchain/semantics/nodes/return.h"
#include "toolchain/semantics/nodes/set_name.h"

namespace Carbon {

auto SemanticsIR::Print(llvm::raw_ostream& out,
                        Semantics::NodeRef node_ref) const -> void {
  switch (node_ref.kind()) {
    case Semantics::NodeKind::BinaryOperator:
      nodes_.Get<Semantics::BinaryOperator>(node_ref).Print(out);
      return;
    case Semantics::NodeKind::Function:
      nodes_.Get<Semantics::Function>(node_ref).Print(
          out, [&](Semantics::NodeRef other) { Print(out, other); });
      return;
    case Semantics::NodeKind::IntegerLiteral:
      nodes_.Get<Semantics::IntegerLiteral>(node_ref).Print(out);
      return;
    case Semantics::NodeKind::Return:
      nodes_.Get<Semantics::Return>(node_ref).Print(out);
      return;
    case Semantics::NodeKind::SetName:
      nodes_.Get<Semantics::SetName>(node_ref).Print(out);
      return;
    case Semantics::NodeKind::Invalid:
      CARBON_FATAL() << "Invalid NodeRef kind";
  }
}

}  // namespace Carbon

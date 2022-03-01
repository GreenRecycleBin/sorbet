#ifndef RUBY_TYPER_LSP_LOCALVARFINDER_H
#define RUBY_TYPER_LSP_LOCALVARFINDER_H

#include "ast/ast.h"
#include <vector>

namespace sorbet::realmain::lsp {

class FieldFinder {
public:
    struct Field {
        core::NameRef name;
        ast::UnresolvedIdent::Kind kind;
    };

private:
    core::Loc queryLoc;
    ast::UnresolvedIdent::Kind queryKind;

    // We go through the effort of keeping track of a method stack so as to not rely on trees having been
    // flattened at this point. (LSP code should try to make minimal assumptions to be robust to changes.)
    std::vector<core::MethodRef> methodStack;

    std::vector<Field> result_;

public:
    FieldFinder(core::Loc queryLoc, ast::UnresolvedIdent::Kind queryKind);

    ast::ExpressionPtr postTransformUnresolvedIdent(core::Context ctx, ast::ExpressionPtr ident);
    ast::ExpressionPtr preTransformMethodDef(core::Context ctx, ast::ExpressionPtr methodDef);
    ast::ExpressionPtr postTransformMethodDef(core::Context ctx, ast::ExpressionPtr methodDef);
    ast::ExpressionPtr preTransformClassDef(core::Context ctx, ast::ExpressionPtr classDef);
    ast::ExpressionPtr postTransformClassDef(core::Context ctx, ast::ExpressionPtr classDef);

    const std::vector<Field> &result() const;
};
}; // namespace sorbet::realmain::lsp

#endif // RUBY_TYPER_LSP_LOCALVARFINDER_H

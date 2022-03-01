#include "FieldFinder.h"
#include "ast/ArgParsing.h"
#include "core/GlobalState.h"

using namespace std;

namespace sorbet::realmain::lsp {

ast::ExpressionPtr FieldFinder::postTransformUnresolvedIdent(core::Context ctx, ast::ExpressionPtr tree) {
    ENFORCE(!methodStack.empty());

    auto &ident = ast::cast_tree_nonnull<ast::UnresolvedIdent>(tree);

    if (ident.kind == ast::UnresolvedIdent::Kind::Local) {
        return tree;
    }

    this->result_.emplace_back(Field{ident.name, ident.kind});
    return tree;
}

ast::ExpressionPtr FieldFinder::preTransformMethodDef(core::Context ctx, ast::ExpressionPtr tree) {
    auto &methodDef = ast::cast_tree_nonnull<ast::MethodDef>(tree);

    ENFORCE(methodDef.symbol.exists());
    ENFORCE(methodDef.symbol != core::Symbols::todoMethod());

    return tree;
}

ast::ExpressionPtr FieldFinder::postTransformMethodDef(core::Context ctx, ast::ExpressionPtr tree) {
    return tree;
}

ast::ExpressionPtr FieldFinder::preTransformClassDef(core::Context ctx, ast::ExpressionPtr tree) {
    return tree;
}

ast::ExpressionPtr FieldFinder::postTransformClassDef(core::Context ctx, ast::ExpressionPtr tree) {
    return tree;
}

const vector<FieldFinder::Field> &FieldFinder::result() const {
    return this->result_;
}

}; // namespace sorbet::realmain::lsp

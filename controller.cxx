#include "controller.hxx"
#include "model.hxx"

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Controller::Controller(Model& model)
        : model_(model),
          view_(model)
{ }

// Controller::Controller()
//     : view_(model_)
//
//     { }

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key) {
    if (key.type() == ge211::Key::Type::up) {
        model_.frog.frog_posn.y -= 1.0;
    }
    if (key.type() == ge211::Key::Type::down) {
        model_.frog.frog_posn.y += 1.0;
    }
    if (key.type() == ge211::Key::Type::left) {
        model_.frog.frog_posn.x -= 1.0;
    }
    if (key.type() == ge211::Key::Type::right) {
        model_.frog.frog_posn.x += 1.0;
    }
}
#include "abstract_gui_element.h"

using namespace core;

size_t AbstractGuiElement::uid_counter_ = 0;

AbstractGuiElement::AbstractGuiElement() :
	uid_(uid_counter_++)
{
}

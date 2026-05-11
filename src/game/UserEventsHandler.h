#pragma once

class UserEventsHandler
{
private:
	sf::RenderWindow* window;
	sf::View* view;


public:
    UserEventsHandler(sf::RenderWindow* window, sf::View* view): window(window), view(view) {};

    UserEventsHandler(UserEventsHandler& src) {
                window = src.window;
				view = src.view;
    }

	void handle(const sf::Event& event) {
        if (event.is<sf::Event::Closed>()) {
            window->close();
        }
        else if (const auto* scrolled = event.getIf<sf::Event::MouseWheelScrolled>()) {
			// If the mouse is captured by ImGui, we don't want to handle the event.
            if (ImGui::GetIO().WantCaptureMouse) return;

            bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);

            if (ctrlPressed) {
                // Zoom is counter-intuitive.
                // Zoom means how much is the view scaled.
                // If zoom is 0.9 it means the view gets smaller,
                // so the world looks bigger.
                if (scrolled->delta > 0) {
                    view->zoom(0.9f);
                }
                else {
                    view->zoom(1.1f);
                }

                window->setView(*view);
            }
        }
	}
};
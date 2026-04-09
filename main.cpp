#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdint>
#include <optional>

int main() {
    // Configuración inicial (Canvas de 710x400)
    sf::RenderWindow window(sf::VideoMode({710, 400}), "SFML 3.0 - Grosor de Linea (Pincel)");
    window.setFramerateLimit(60);

    // En lugar de líneas, guardamos círculos para simular el grosor
    std::vector<sf::CircleShape> brushStrokes;
    
    // El radio es la mitad del grosor deseado (Grosor 10 -> Radio 5)
    float brushRadius = 5.0f;

    while (window.isOpen()) {
        // Manejo de eventos (Sintaxis SFML 3.0)
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Lógica de dibujo (Mouse Dragged)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

            // Creamos un "punto" de dibujo con grosor
            sf::CircleShape point(brushRadius);
            point.setOrigin({brushRadius, brushRadius}); // Centrar el círculo en el mouse
            point.setPosition(mousePos);

            // Lógica de color (Simulando HSB de p5.js)
            float diff = mousePos.x - mousePos.y;
            sf::Color color;
            color.r = static_cast<std::uint8_t>(std::fmod(std::abs(diff), 255.0f));
            color.g = 150;
            color.b = 230;
            
            point.setFillColor(color);

            // Guardamos el círculo en nuestro "lienzo"
            brushStrokes.push_back(point);
        }

        // Renderizado
        window.clear(sf::Color::Black);

        // Dibujamos todos los círculos acumulados
        for (const auto& stroke : brushStrokes) {
            window.draw(stroke);
        }

        window.display();
    }

    return 0;
}
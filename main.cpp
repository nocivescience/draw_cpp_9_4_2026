#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdint>
#include <optional>

// Estructura para almacenar cada segmento de línea dibujado
struct LineSegment {
    sf::Vertex start;
    sf::Vertex end;
};

int main() {
    // SFML 3.0: Constructor con sf::VideoMode({ancho, alto})
    sf::RenderWindow window(sf::VideoMode({710, 400}), "P5.js to SFML 3.0 - Drawing");
    window.setFramerateLimit(60);

    // Contenedor para persistencia del dibujo
    std::vector<LineSegment> segments;
    
    sf::Vector2f lastMousePos;
    bool isFirstPoint = true;

    // Bucle principal (Game Loop)
    while (window.isOpen()) {
        
        // SFML 3.0: Nuevo sistema de eventos usando std::optional
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // Cerrar también con la tecla Escape (Ejemplo de Key Event en SFML 3)
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }

        // Detección de dibujo (Mouse Dragged)
        // SFML 3.0 requiere el scope completo: sf::Mouse::Button::Left
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2f currentMousePos = sf::Vector2f(sf::Mouse::getPosition(window));

            if (!isFirstPoint && currentMousePos != lastMousePos) {
                // Lógica de color basada en posición (Simulando HSB)
                float diff = currentMousePos.x - currentMousePos.y;
                sf::Color color;
                color.r = static_cast<std::uint8_t>(std::fmod(std::abs(diff), 255.0f));
                color.g = 150;
                color.b = 230;

                // SFML 3.0: Inicialización directa de sf::Vertex
                sf::Vertex v1;
                v1.position = lastMousePos;
                v1.color = color;

                sf::Vertex v2;
                v2.position = currentMousePos;
                v2.color = color;

                segments.push_back({v1, v2});
            }
            lastMousePos = currentMousePos;
            isFirstPoint = false;
        } else {
            // Resetear el rastro cuando se suelta el botón
            isFirstPoint = true;
        }

        // Renderizado
        window.clear(sf::Color::Black);

        // Dibujar todos los segmentos acumulados en el vector
        for (const auto& seg : segments) {
            sf::Vertex line[] = { seg.start, seg.end };
            window.draw(line, 2, sf::PrimitiveType::Lines);
        }

        window.display();
    }

    return 0;
}
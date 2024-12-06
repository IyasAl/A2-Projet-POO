#include "../include/Button.h" //Inclut le fichier d'en-tête Button.h
#include <stdexcept>//Permet de gérer les exceptions, notamment pour signaler les erreurs critiques comme le chargement de polices.


// Constructeur : Initialise un bouton avec une position (x, y), des dimensions (width, height),
// une étiquette (label), et une police de caractère (fontFile).

Button::Button(float x, float y, float width, float height, const std::string& label, const sf::Font& fontFile) {

    // Charge la police depuis un fichier. Si le chargement échoue...
    if (!font.loadFromFile("./asset/font/league-spartan.bold.ttf")) {
        if (!font.loadFromFile("./asset/font/league-spartan.bold.ttf")) { // Une tentative secondaire de chargement de la police est faite (pour assurer une redondance).
            throw std::runtime_error("Failed to load font!"); // Si cela échoue à nouveau, une exception est levée.
        }
    }

    // Configure la forme du bouton
    shape.setPosition(x, y); // Définit la position du bouton en haut à gauche.
    shape.setSize(sf::Vector2f(width, height)); // Définit la taille du bouton avec les dimensions spécifiées.
    shape.setFillColor(sf::Color::White); // Applique une couleur de fond blanche au bouton.
    shape.setOutlineColor(sf::Color::Black); // Ajoute un contour noir au bouton.
    shape.setOutlineThickness(2); // Définit l'épaisseur du contour à 2 pixels.

    // Configure le texte du bouton
    text.setFont(font); // Associe la police chargée au texte affiché sur le bouton
    text.setString(label); // Définit le texte du bouton à l'aide de l'étiquette (label) fournie.
    text.setCharacterSize(20); // Spécifie la taille des caractères du texte.
    text.setFillColor(sf::Color::Black); // Définit la couleur du texte en noir.

    // Centre le texte à l'intérieur du bouton
    sf::FloatRect textBounds = text.getLocalBounds(); // Obtient les dimensions et les coordonnées du texte (dimensions du rectangle englobant).
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f); // Centre le texte en ajustant son origine à son centre géométrique.
    text.setPosition(x + width / 2.0f, y + height / 2.0f); // Positionne le texte au centre du bouton en ajustant sa position par rapport à la taille du bouton.
}

void Button::setOnClick(const std::function<void()>& callback) {// Définit une fonction de rappel (callback) qui sera exécutée lorsque le bouton est cliqué.
    onClick = callback;
}

void Button::setFillColor(const sf::Color& color) {// Change la couleur de fond du bouton avec la couleur spécifiée.
    shape.setFillColor(color); 
}

void Button::setOutlineColor(const sf::Color& color) { // Change la couleur du contour du bouton avec la couleur spécifiée.
    shape.setOutlineColor(color);
}

void Button::setTextColor(const sf::Color& color) { // Change la couleur du texte du bouton avec la couleur spécifiée.
    text.setFillColor(color);
}

bool Button::isPressed(const sf::Vector2i& mousePos, const sf::Event& event) const {
   // Vérifie si le bouton a été cliqué en :
    
    return event.type == sf::Event::MouseButtonPressed && 
           event.mouseButton.button == sf::Mouse::Left && // 1. Vérifiant que l'événement est un clic de souris gauche.
           shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)); // 2. Vérifiant que la position de la souris est dans les limites du bouton.
}


void Button::render(sf::RenderWindow& window) { // Dessine le bouton dans la fenêtre graphique SFML :
    window.draw(shape); // 1. Dessine la forme rectangulaire représentant le bouton.
    window.draw(text); // 2. Dessine le texte affiché sur le bouton.
}

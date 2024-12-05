#pragma once //Directive qui garantit que le fichier d’en-tête n'est inclus qu'une seule fois dans le processus de compilation

#include <SFML/Graphics.hpp> //Inclut la bibliothèque SFML pour les fonctionnalités graphiques, notamment pour dessiner la grille à l'écran
#include <functional> //Permet d'utiliser std::function, qui est un type générique pour stocker et appeler des fonctions
#include <string> //pour utiliser la classe std::string pour manipuler des chaînes de caractères

class Button { 
private:
    sf::RectangleShape shape;     // Représente la forme visuelle du bouton
    sf::Text text;                // Texte affiché sur le bouton
    sf::Font font;                // Police utilisée pour le texte
    std::function<void()> onClick; // Fonction de callback pour gérer les clics sur le bouton

public:
     // Constructeur : Initialise un bouton avec une position, une taille, un texte, et une police.
    Button(float x, float y, float width, float height, const std::string& label, const sf::Font& fontFile);

    // Définit la fonction à appeler lorsque le bouton est cliqué
    void setOnClick(const std::function<void()>& callback);

    //Change la couleur de fond du bouton
    void setFillColor(const sf::Color& color);

    // Change la couleur du contour du bouton
    void setOutlineColor(const sf::Color& color);

    // Change la couleur du texte
    void setTextColor(const sf::Color& color);

    // Dessine le bouton dans une fenêtre SFML
    void render(sf::RenderWindow& window);
    // Vérifie si le bouton a été cliqué
    bool isPressed(const sf::Vector2i& mousePos, const sf::Event& event) const;
};

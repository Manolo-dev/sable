# Sable

Sable est une petite bibliothèque/API graphique en C pur. Elle dessine une arborescence de `Div` dans un buffer de pixels, sans dépendance à une plateforme ni à une bibliothèque graphique.

## Fonctionnalités principales

- **Arbre de `Div`** à la manière du DOM HTML/JS : chaque élément possède un style, une
  position, des enfants, et se compose récursivement.
- **Rendu dans un `Buffer`** : un pointeur de pixels, une largeur, une hauteur,
  un stride.
- **Formes définies par champ de distance signé (SDF)** : rectangle, cercle,
  squircle (courbe de Lamé).
- **Anti-aliasing** par sous-échantillonnage.
- **Transformations 2D** : rotation, translation, échelle, et projection
  perspective (`rotate_x`, `rotate_y`).
- **Tests de collision** (`div_hit`, `div_signed_distance`) et callbacks
  `onclick`.

### Fonctionnalités futures

- Formes supplémentaires : image, polygones, étoiles, chemins arbitraires.
- Clipping, scroll et zoom.
- Rendu d'image.
- Rendu de texte via polices SDF.
- Ombres, bordures, dégradés.
- Rendu SVG.

### Fonctionnalités secondaires

- Cache de rendu pour les sous-arbres statiques.
- Groupes et compositions.

## Portabilité

Sable ne connaît que le C standard (`stdint.h`, `math.h`) et un buffer de pixels. Elle tourne sur Android (via `NativeActivity`), sur Linux (framebuffer, X11, Wayland...), et n'importe où ailleurs dès que l'on peut remplir un `Buffer`. Il sert notamment à créer des images, par exemple `ppm`. Aucun appel système, aucune allocation globale, aucune dépendance externe.

## Philosophie du projet

Sable part d'une idée simple : dessiner une interface ne devrait pas exiger une stack graphique massive. Un buffer de pixels et quelques primitives claires suffisent. La bibliothèque reste petite, lisible, sans dépendance, et se laisse embarquer n'importe où.

## Contribution

Les contributions sont les bienvenues. Pour participer, ouvrez une issue ou soumettez une pull request sur GitHub, et n'hésitez pas à lire le [PLAN](PLAN.md) pour le plan de développement, les conventions à respecter, etc. Gardez à l'esprit les contraintes du projet : pas de dépendance externe, pas d'allocation cachée, du C standard.

## Licence

Sable est distribué sous la licence GPL-3.0-only. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

## Acknowledgments

Merci à tous les contributeurs et aux communautés open-source dont les idées ont nourri ce projet.

Et -- étonnamment -- merci à Nvidia, à Google, ainsi qu'aux équipes de SDL, d'OpenGL, d'OpenCL et de Vulkan : utiliser vos outils, faire la tuyauterie pour chaque système, comprendre vos infamies, tout cela m'a paru plus complexe que de tout recréer de zéro. Il m'a semblé plus simple de réinventer la roue depuis le début que d'utiliser vos roues carrées (je suis méchant, désolé. Je n'aime juste pas le boilerplate).

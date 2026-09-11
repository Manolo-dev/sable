# Sable

Sable est une petite bibliothèque graphique portable en C pur. Elle dessine une arborescence de `Div` dans un simple buffer de pixels, sans dépendance à une plateforme ni à une bibliothèque graphique.

## Fonctionnalités principales

- **Arbre de `Div`** à la manière du DOM : chaque élément possède un style, une
  position, des enfants, et se compose récursivement.
- **Formes définies par champ de distance signé (SDF)** : rectangle, cercle,
  squircle (courbe de Lamé).
- **Anti-aliasing** par sous-échantillonnage.
- **Transformations 2D** : rotation, translation, échelle, et projection
  perspective (`rotate_x`, `rotate_y`).
- **Ancrages** (`LEFT_TOP`, `CENTER`, `RIGHT_BOTTOM`...), opacité, composition
  alpha.
- **Rendu dans un `Buffer`** : un pointeur de pixels, une largeur, une hauteur,
  un stride. C'est tout.
- **Tests de collision** (`div_hit`, `div_signed_distance`) et callbacks
  `onclick`.

### Fonctionnalités futures

- Formes supplémentaires : polygones, étoiles, chemins arbitraires.
- Clipping et scroll.
- Rendu d'image.
- Rendu de texte via polices SDF.
- Ombres, bordures, dégradés.

### Fonctionnalités secondaires

- Cache de rendu pour les sous-arbres statiques.
- Groupes et compositions.
- Transitions et easing sur les propriétés de style.

## Portabilité

Sable ne connaît que le C standard (`stdint.h`, `math.h`) et un buffer de pixels. Elle tourne sur Android (via `NativeActivity`), sur Linux (framebuffer, X11, Wayland...), et n'importe où ailleurs dès qu'on sait remplir un `Buffer`. Aucun appel système, aucune allocation globale, aucune dépendance externe.

## Philosophie du projet

Sable part d'une idée simple : dessiner une interface ne devrait pas exiger une stack graphique massive. Un buffer de pixels et quelques primitives claires suffisent. La bibliothèque reste petite, lisible, sans dépendance, et se laisse embarquer n'importe où -- y compris là où on ne l'attend pas.

## Contribution

Les contributions sont les bienvenues. Pour participer, ouvrez une issue ou soumettez une pull request sur GitHub, et n'hésitez pas à lire le [PLAN](PLAN.md) pour le plan de développement, les conventions à respecter, etc. Gardez à l'esprit les contraintes du projet : pas de dépendance externe, pas d'allocation cachée, du C standard.

## Licence

Sable est distribué sous la licence GPL-3.0-only. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

## Acknowledgments

Merci à tous les contributeurs et aux communautés open-source dont les idées ont nourri ce projet.

Et -- étonnamment -- merci à Nvidia, à Google, ainsi qu'aux équipes de SDL, d'OpenGL, d'OpenCL et de Vulkan : utiliser vos outils, faire la tuyauterie pour chaque système, comprendre vos infamies, tout cela m'a paru plus complexe que de tout recréer de zéro. Il m'a semblé plus simple de réinventer la roue depuis le début que d'utiliser vos roues carrées (je suis méchant, désolé. J'aimer juste pas le boilerplate).
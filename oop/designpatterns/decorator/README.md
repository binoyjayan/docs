### Decorator design pattern

- Used to decorate objects
- A dynamic decorator keeps the referene to the decorated objects
  - e.g. ColoredShape(Shape())
- A static decorator uses mixin inheritance using template
  - ColoredShape<Square>
- Both approaches allow limitless composition
  - TransparentShape<ColoredShape<Circle>>

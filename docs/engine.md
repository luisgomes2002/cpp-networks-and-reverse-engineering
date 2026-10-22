# Engine API

The engine contains reusable systems that do not depend on game-specific
types such as `Player`, `Mob`, `Character`, or combat rules.

## Data types

### `Vec2`

`Vec2` stores a grid position in world units.

- `column`: horizontal position.
- `line`: vertical position.

### `GameObject`

`GameObject` is the generic entity handled by engine systems.

- `img`: text used when drawing the object.
- `tag`: category used to filter objects. Its default value is `"object"`.
- `position`: object position as a `Vec2`.

The engine does not own `GameObject` instances. The game creates and owns
them, then passes pointers to the engine when it needs drawing or proximity
detection.

## Functions

### `char readKey()`

Waits for a single keyboard key and returns it as a `char`.

- On Windows, it uses `_getch()`.
- On Linux, it temporarily switches the terminal to non-canonical, no-echo
  mode and restores the previous terminal settings before returning.

### `void drawMap(const GameObject &player, const std::vector<GameObject *> &objects, int tileLength)`

Draws a square text map to standard output.

- `player`: the object drawn as the player.
- `objects`: non-owning pointers to objects that can be drawn on the map.
- `tileLength`: both the map width and height in tiles; it is also used to
  convert world coordinates into tile coordinates.

The function draws walls on the map boundary, the player at its tile, and then
the first object found at each remaining tile. Empty tiles are drawn as ground.

### `std::vector<GameObject *> detectObjectsInRadius(GameObject &center, std::vector<GameObject *> &objects, std::vector<std::string> &tags, int radius, int tileLength)`

Returns the objects near a center object, without applying game rules.

- `center`: the object from which distance is measured.
- `objects`: non-owning pointers to candidate objects.
- `tags`: only objects whose `tag` exists in this list are considered.
- `radius`: maximum horizontal and vertical distance in tiles.
- `tileLength`: converts world coordinates into tile coordinates.

Distance is evaluated independently on each axis, so the search area is a
square centered on `center`. The center tile itself is excluded. The returned
pointers refer to the original objects; no objects are copied or owned by the
engine.

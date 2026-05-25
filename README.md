# LuaGame 0.0.1

LuaGame is a simple 2D game library for Lua.

## Features

- Window creation
- Rendering
- Rectangles
- Images
- Text
- Keyboard input

---

# Install Dependencies

Ubuntu / Debian:

```bash
make deps
```

---

# Compile

```bash
make build
```

---

# Install Library

```bash
make install
```

---

# Configure Lua Path

```bash
export LUA_CPATH="$HOME/.local/lib/lua/5.4/?.so;;"
```

Permanent:

```bash
echo 'export LUA_CPATH="$HOME/.local/lib/lua/5.4/?.so;;"' >> ~/.bashrc

source ~/.bashrc
```

---

# Project Structure

```text
LuaGame/
├── bi.c, main.lua
├── Makefile
├── README.md
```

---

# Available Functions

## Create Window

```lua
window(title, width, height)
```

Example:

```lua
window("LuaGame", 800, 600)
```

---

## Clear Screen

```lua
clear(r, g, b)
```

Example:

```lua
clear(20, 20, 20)
```

---

## Draw Rectangle

```lua
rect(x, y, width, height, r, g, b)
```

Example:

```lua
rect(100, 100, 200, 150, 255, 0, 0)
```

---

## Load Image

```lua
image(path)
```

Example:

```lua
image("player.png")
```

---

## Draw Image

```lua
draw(x, y, width, height)
```

Example:

```lua
draw(100, 100, 128, 128)
```

---

## Draw Text

```lua
text(message, x, y)
```

Example:

```lua
text("LuaGame", 20, 20)
```

---

## Keyboard Input

```lua
key("KEY")
```

Example:

```lua
if key("D") then
    x = x + 5
end
```

---

## Main Loop

```lua
while running() do

end
```

---

# Example

```lua
require("game")

window("LuaGame", 800, 600)

x = 100

while running() do
    clear(20, 20, 20)

    if key("D") then
        x = x + 5
    end

    if key("A") then
        x = x - 5
    end

    rect(x, 100, 200, 150, 255, 0, 0)

    text("LuaGame", 20, 20)
end
```

---

# License

MIT

require("game")

window("Teste", 800, 600)

image("pl.png")

x = 100

while running() do
    clear(20, 20, 20)

    if key("D") then
        x = x + 5
    end

    if key("A") then
        x = x - 5
    end

    draw(x, 100, 128, 128)

    text("Lua Engine", 20, 20)
end

# Regras de arquitetura

## Engine

A engine contém código genérico e reutilizável:

- `GameObject`
- `Vec2`
- leitura de teclado
- desenho do mapa
- detecção de objetos próximos

A engine não conhece nenhuma classe específica do jogo. Portanto, arquivos em
`engine/` não devem incluir arquivos de `game/` ou depender de `Player`, `Mob`,
`Character` ou `combat()`.

Exemplo correto:

```cpp
std::vector<GameObject *> detectObjectsInRadius(...);
```

A função informa quais objetos estão próximos, sem decidir o que fazer com eles.

## Jogo

A pasta `game/` contém regras específicas deste jogo:

- `Character`
- `Player`
- `Mob`
- ataque e combate

O jogo pode incluir e chamar funções da engine.

Exemplo:

```text
combat.cpp chama detectObjectsInRadius()
combat.cpp verifica se o GameObject pertence a um Mob
combat.cpp inicia combat()
```

## Donos dos objetos

`GameObject` pertence à engine e não deve guardar ponteiros para `Character`,
`Player` ou `Mob`.

O jogo mantém os objetos reais:

```cpp
Mob mob1(...);
Mob mob2(...);
```

E cria referências para a engine desenhar e detectar:

```cpp
std::vector<GameObject *> objects = {
	&mob1.gameObject,
	&mob2.gameObject};
```

Também mantém a lista de mobs:

```cpp
std::vector<Mob *> mobs = {
	&mob1,
	&mob2};
```

Assim, não são criadas cópias de `GameObject`.

## Fluxo atual de combate

```text
main.cpp
  -> chama checkCombat()

game/combat.cpp
  -> chama detectObjectsInRadius() da engine
  -> encontra o Mob ligado ao GameObject retornado
  -> chama combat()

engine/collision.cpp
  -> apenas encontra GameObject próximos
```

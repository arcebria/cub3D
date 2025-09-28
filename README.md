# 🕹️ **Proyecto cub3D** 🚀

**cub3D** es uno de los retos gráficos más apasionantes de 42: crear un pequeño motor 3D tipo raycaster en C, inspirado en los clásicos como Wolfenstein 3D.  
🧑‍💻 El objetivo era comprender los fundamentos de los motores gráficos, renderizar mapas en 3D a partir de una vista en primera persona y gestionar la interacción del usuario.

---

## ✨ **Lo que aprendí realizando el proyecto**

Durante el desarrollo de cub3D, adquirí conocimientos clave en programación gráfica y gestión avanzada de recursos en C:

- 🖥️ **Renderizado 3D con raycasting**  
  Implementé el algoritmo de raycasting para simular una vista en primera persona y renderizar paredes, suelos y techos en tiempo real.

- 🗺️ **Parsing y validación de mapas**  
  Desarrollé lógica para leer, validar y procesar mapas en formato `.cub`, gestionando texturas, colores y la posición inicial del jugador.

- 🎨 **Gestión de texturas y colores**  
  Aprendí a cargar y aplicar texturas a las paredes, así como a configurar los colores del suelo y techo.

- 🕹️ **Interacción y movimiento**  
  Implementé controles para mover al jugador, girar la cámara y detectar colisiones con las paredes del mapa.

- 🛡️ **Gestión de errores y memoria**  
  Aseguré la correcta gestión de errores y liberación de memoria, evitando fugas y comportamientos inesperados.

- 📚 **Uso de librerías propias (libft) y MLX42**  
  Integré funciones de mi propia librería (**libft**) y utilicé la librería gráfica **MLX42** para la creación de ventanas y manejo de eventos.

---

## 🏁 **El resultado final**

El resultado fue un **motor gráfico funcional** capaz de renderizar mapas en 3D, gestionar texturas, colores y permitir la navegación en primera persona.  
Este proyecto me dio una base sólida para comprender los principios de los motores gráficos y la programación interactiva.

---

## ⚡ **Ejemplo de uso**

```sh
./cub3D mapa.cub
```

Controles básicos:
- `W`, `A`, `S`, `D`: Mover al jugador
- `←`, `→`: Girar la cámara
- **Ratón**: Girar la cámara moviendo el ratón
- `P`: Mostrar el sprite de la pistola
- **Click izquierdo** o **Shift izquierdo**: Activar la animación de disparo
- `ESC`: Salir del programa

---

## 🛠️ **Compilación**

```sh
make
```

Esto genera el ejecutable `cub3D` en el directorio raíz.

---

## 📁 **Estructura del proyecto**

```
cub3D/
├── inc/                # Cabeceras (.h)
├── libft/              # Librería auxiliar libft
├── MLX42/              # Librería gráfica MLX42 (tras hacer make)
├── src/                # Código fuente organizado por módulos
├── texs/               # Texturas utilizadas en el juego
├── maps/               # Mapas de ejemplo en formato .cub
└── Makefile
```
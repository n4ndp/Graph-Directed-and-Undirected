# **Graphs | `Directed` and `Undirected`**

Esta implementación en C++ proporciona un grafo ponderado (dirigido o no dirigido) que representa una red de aeropuertos y sus conexiones.

## **Conjunto de Datos: [Aeropuertos Peruanos](https://raw.githubusercontent.com/n4ndp/Graph/main/data/pe.json)**

Este conjunto de datos contiene información detallada sobre cada aeropuerto. La estructura de los datos es la siguiente:

```json
[
    {
        "City": "Juliaca",
        "DBTZ": "U",
        "Name": "Juliaca",
        "Country": "Peru",
        "IATA/FAA": "JUL",
        "Longitude": "-70.158169",
        "ICAO": "SPJL",
        "Airport ID": "2792",
        "Latitude": "-15.467103",
        "Timezone": "12552",
        "DST": "-5",
        "destinations": [
            "2802",
            "2812",
            "2789"
        ]
    },
    ...
]
```

## **Características**

- **Grafo Dirigido y No Dirigido:** La implementación soporta ambos tipos de grafos, permitiendo modelar las conexiones entre aeropuertos con distintas direcciones y pesos.
- **Ponderación de Aristas:** Las aristas están ponderadas con la distancia calculada usando la fórmula de Haversine, la cual considera la curvatura de la Tierra.
- **Carga de Datos:** Los datos se cargan desde un archivo JSON que contiene información de aeropuertos y sus destinos.

## **Cómo Usar**

Utiliza un compilador de C++ que soporte C++11 o superior. Por ejemplo, si usas `g++`, el comando de compilación puede ser:

```bash
g++ -std=c++11 -o tu_programa main.cpp
```

Una vez compilado, ejecuta el programa. Asegúrate de que el archivo `pe.json` esté ubicado en el directorio `data` dentro del directorio de trabajo. Puedes ejecutar el programa con:

```bash
./tu_programa
```

Si todo está configurado correctamente, el programa construirá el grafo de aeropuertos y mostrará las conexiones junto con las distancias ponderadas entre los aeropuertos.

## **Ejemplo de Salida**

```
Vertex: 2812 -> Teniente Alejandro Velasco Astete Intl
  Edge to 2792 with weight 287.857
  Edge to 2802 with weight 314.272
  Edge to 2808 with weight 310.932
  Edge to 2789 with weight 585.912
Vertex: 2788 -> Comandante Fap German Arias Graziani
  Edge to 2789 with weight 302.051
Vertex: 2781 -> Cap Fap David Abenzur Rengifo Intl
  Edge to 2806 with weight 287.294
  Edge to 2789 with weight 491.343
  Edge to 2801 with weight 529.551
Vertex: 2786 -> Coronel Fap Alfredo Mendivil Duarte
  Edge to 2789 with weight 339.981
Vertex: 2792 -> Juliaca
  Edge to 2789 with weight 843.226
  Edge to 2812 with weight 287.857
...
```

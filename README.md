# **Graph | `Directed` and `Undirected`**

This C++ implementation provides a weighted graph capable of representing and managing connections between airports. By assigning weights to edges, it effectively models the complexity and distance between these locations, enabling efficient modeling of air routes and their relationships.

## **Dataset: [Peruvian Airports](https://raw.githubusercontent.com/n4ndp/Graph/main/data/pe.json?token=GHSAT0AAAAAACJDGABQ3DNPYXUHO5DQNDYMZKXFZJQ)**

The dataset offers detailed information on different airports:

```json
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
```

This dataset contains detailed information about each airport, including name, geographical location, unique identifications (IATA/FAA, ICAO), and a list of connected destinations from that airport.

## **Example Usage**

```bash
$ g++ main.cpp -o airport_graph
$ ./airport_graph pe.json 2789
```

**Output (Specific Airport Information):**

```
Vertex 2789 (data: Jorge Chavez Intl):
    Edge to vertex 2812 (data: Teniente Alejandro Velasco Astete Intl) with weight 585912
    Edge to vertex 2788 (data: Comandante Fap German Arias Graziani) with weight 302051
    Edge to vertex 2804 (data: Capitan Carlos Martinez De Pinillos) with weight 489540
    Edge to vertex 2786 (data: Coronel Fap Alfredo Mendivil Duarte) with weight 339982
    Edge to vertex 6067 (data: Alferez Fap David Figueroa Fernandini Airport) with weight 258156
    Edge to vertex 2781 (data: Cap Fap David Abenzur Rengifo Intl) with weight 491344
    Edge to vertex 2806 (data: Cadete Guillermo Del Castillo Paredes) with weight 618401
    Edge to vertex 6066 (data: Mayor General FAP Armando Revoredo Iglesias Airport) with weight 563464
    Edge to vertex 2807 (data: Coronel Carlos Ciriani Santa Rosa Intl) with weight 994201
    Edge to vertex 2802 (data: Rodriguez Ballon) with weight 765519
    Edge to vertex 2785 (data: Capt Jose A Quinones Gonzales Intl) with weight 653705
    Edge to vertex 2801 (data: Coronel Francisco Secada Vignetta Intl) with weight 1.00711e+06
    Edge to vertex 2792 (data: Juliaca) with weight 843225
    Edge to vertex 2787 (data: Andahuaylas) with weight 448947
    Edge to vertex 2808 (data: Padre Aldamiz) with weight 859153
    Edge to vertex 2809 (data: Capitan Fap Guillermo Concha Iberico) with weight 850000
    Edge to vertex 2796 (data: Pedro Canga) with weight 1.00806e+06
```

Now, if no second argument is provided after `pe.json`, the output will display information about all airports in the dataset, including their connections and distances.

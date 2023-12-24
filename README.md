# **Graph | `Directed` and `Undirected`**

This C++ implementation provides a weighted graph (directed or undirected) that represents a network of airports and their connections. Additionally, within the 'Algorithms' folder, you can find various algorithms designed to traverse the graph and determine the shortest path between two airports.

## **Dataset: [Peruvian Airports](https://raw.githubusercontent.com/n4ndp/Graph/main/data/pe.json)**

This dataset contains detailed information about each airport, The data is structured as follows:

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

## **Graph**

```textplain
Vertex 2812 (data: Teniente Alejandro Velasco Astete Intl):
        Edge to vertex 2802 (data: Rodriguez Ballon) with weight 314272
        Edge to vertex 2792 (data: Juliaca) with weight 287856
        Edge to vertex 2808 (data: Padre Aldamiz) with weight 310932
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 585912
Vertex 2789 (data: Jorge Chavez Intl):
        Edge to vertex 2812 (data: Teniente Alejandro Velasco Astete Intl) with weight 585912
        Edge to vertex 2787 (data: Andahuaylas) with weight 448947
        Edge to vertex 2804 (data: Capitan Carlos Martinez De Pinillos) with weight 489540
        Edge to vertex 2788 (data: Comandante Fap German Arias Graziani) with weight 302051
        Edge to vertex 2786 (data: Coronel Fap Alfredo Mendivil Duarte) with weight 339982
        Edge to vertex 2808 (data: Padre Aldamiz) with weight 859153
        Edge to vertex 6067 (data: Alferez Fap David Figueroa Fernandini Airport) with weight 258156
        Edge to vertex 2806 (data: Cadete Guillermo Del Castillo Paredes) with weight 618401
        Edge to vertex 2785 (data: Capt Jose A Quinones Gonzales Intl) with weight 653705
        Edge to vertex 6066 (data: Mayor General FAP Armando Revoredo Iglesias Airport) with weight 563464
        Edge to vertex 2801 (data: Coronel Francisco Secada Vignetta Intl) with weight 1.00711e+06
        Edge to vertex 2792 (data: Juliaca) with weight 843225
        Edge to vertex 2802 (data: Rodriguez Ballon) with weight 765519
        Edge to vertex 2796 (data: Pedro Canga) with weight 1.00806e+06
        Edge to vertex 2809 (data: Capitan Fap Guillermo Concha Iberico) with weight 850000
        Edge to vertex 2781 (data: Cap Fap David Abenzur Rengifo Intl) with weight 491344
        Edge to vertex 2807 (data: Coronel Carlos Ciriani Santa Rosa Intl) with weight 994201
Vertex 2781 (data: Cap Fap David Abenzur Rengifo Intl):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 491344
        Edge to vertex 2806 (data: Cadete Guillermo Del Castillo Paredes) with weight 287294
        Edge to vertex 2801 (data: Coronel Francisco Secada Vignetta Intl) with weight 529551
Vertex 2786 (data: Coronel Fap Alfredo Mendivil Duarte):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 339982
Vertex 2792 (data: Juliaca):
        Edge to vertex 2812 (data: Teniente Alejandro Velasco Astete Intl) with weight 287856
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 843225
        Edge to vertex 2802 (data: Rodriguez Ballon) with weight 180728
Vertex 2796 (data: Pedro Canga):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 1.00806e+06
Vertex 6067 (data: Alferez Fap David Figueroa Fernandini Airport):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 258156
Vertex 2809 (data: Capitan Fap Guillermo Concha Iberico):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 850000
Vertex 6066 (data: Mayor General FAP Armando Revoredo Iglesias Airport):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 563464
Vertex 2787 (data: Andahuaylas):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 448947
Vertex 2802 (data: Rodriguez Ballon):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 765519
        Edge to vertex 2812 (data: Teniente Alejandro Velasco Astete Intl) with weight 314272
        Edge to vertex 2807 (data: Coronel Carlos Ciriani Santa Rosa Intl) with weight 235649
        Edge to vertex 2792 (data: Juliaca) with weight 180728
Vertex 2801 (data: Coronel Francisco Secada Vignetta Intl):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 1.00711e+06
        Edge to vertex 2781 (data: Cap Fap David Abenzur Rengifo Intl) with weight 529551
        Edge to vertex 2806 (data: Cadete Guillermo Del Castillo Paredes) with weight 454862
Vertex 2806 (data: Cadete Guillermo Del Castillo Paredes):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 618401
        Edge to vertex 2781 (data: Cap Fap David Abenzur Rengifo Intl) with weight 287294
        Edge to vertex 2801 (data: Coronel Francisco Secada Vignetta Intl) with weight 454862
Vertex 2788 (data: Comandante Fap German Arias Graziani):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 302051
Vertex 2807 (data: Coronel Carlos Ciriani Santa Rosa Intl):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 994201
        Edge to vertex 2802 (data: Rodriguez Ballon) with weight 235649
Vertex 2808 (data: Padre Aldamiz):
        Edge to vertex 2812 (data: Teniente Alejandro Velasco Astete Intl) with weight 310932
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 859153
Vertex 2804 (data: Capitan Carlos Martinez De Pinillos):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 489540
Vertex 2785 (data: Capt Jose A Quinones Gonzales Intl):
        Edge to vertex 2789 (data: Jorge Chavez Intl) with weight 653705
```

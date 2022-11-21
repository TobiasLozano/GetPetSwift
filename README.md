# GetPetSwift 
Este proyecto está dividido en 2 partes, el dispositivo GPS y la pagina que muestra la informacion.

# Dispositivo GPS
Funciona gracias al microcontrolador ESP-32, fue programado en C++.
Librerias usadas:

### `TinyGPS`
### `WifiClientSecure`
### `HTTPClient`

De esta forma, se obtienen los datos tomados por un sensor y se envían a una base de datos.

# Pagina web:
La url de esta, es:
https://getpetswift.netlify.app/

Es la interfaz del usuario final, se encarga de traer los datos de la base de datos para mostrar las coordenadas tomadas junto con un mapa que ubique las mismas.


Tecnologias usadas:

### `HTML5`
### `CSS3`
### `Javascript`
 
Hosting compartido:
### `Netlify`
Base de datos:
### `Google Sheets`

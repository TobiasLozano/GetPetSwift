longitudElement = document.getElementById("long");
latitudElement = document.getElementById("lat");
horaElement = document.getElementById("hora");
ahoraElement = document.getElementById("ahora");
const boton = document.getElementById("boton");
boton.onclick = () => {
  fetch("https://sheet.best/api/sheets/85b1faa7-57e6-404f-80b7-7531a679eeef")
    .then((response) => response.json())
    .then((data) => {
      let ultimoDato = data[data.length - 1];
      let longitud = ultimoDato.Longitud;
      let latitud = ultimoDato.Latitud;
      let hora = ultimoDato.Hora;
      let tiempo = new Date("14/11/2022 7:52:33");
      let ahora = new Date(),
        ahoraFormateada =
          [ahora.getDate(), ahora.getMonth() + 1, ahora.getFullYear()].join(
            "/"
          ) +
          " " +
          [ahora.getHours(), ahora.getMinutes(), ahora.getSeconds()].join(":");
      console.log(ultimoDato);
      console.log(latitud, longitud, hora, ahoraFormateada);
      longitudElement.textContent = longitud;
      latitudElement.textContent = latitud;
      horaElement.textContent = hora;
      ahoraElement.textContent = ahoraFormateada;
      let url =  `https://maps.google.com/?q=${latitud},${longitud}`
      open(url, "Ubicacion", "width=700, height=500")
    });
};


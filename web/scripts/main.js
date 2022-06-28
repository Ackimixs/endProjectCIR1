import planetEulerAsy from "./planets-EulerAsy.json" assert {type : "json"}
import planetEuler from "./planets-Euler.json" assert {type : "json"}
import planetSetup from "./planetSetup.json" assert {type : "json"}
import Card from "./card.json" assert {type : "json"}

let blacklistPlanet = [];

let typeMethod = "eulerAsy"

let sunRadius = 20000000000

let scale = 600000000;

let rangeValue = 1;

let speed = 1

let canvas = document.getElementById("solarSystem");
let context = canvas.getContext("2d");

let size;
canvas.height < canvas.width ?
    size = canvas.height
    :size = canvas.width

function drawSun() {
    context.save();
    context.beginPath();
    context.fillStyle = "yellow"
    context.arc(size/2, size/2, sunRadius/scale, 0, Math.PI*2, false);
    context.closePath();
    context.fill();
    context.restore();
}


function drawPlanetTrajectory(name) {
    context.save();
    context.translate(canvas.width/2, canvas.height/2)
    context.beginPath();

    if (planetSetup[name + "-" + typeMethod].time > planetSetup[name + "-" + typeMethod].numberOfPoints-speed) {
        planetSetup[name + "-" + typeMethod].time = 1;
    }

    context.strokeStyle = planetSetup[name + "-" + typeMethod].color

    for (let i = 0; i < planetSetup[name + "-" + typeMethod].numberOfPoints; i++) {

        context.lineTo(planetSetup[name + "-" + typeMethod].trajectory[i][0][0]/scale , planetSetup[name + "-" + typeMethod].trajectory[i][0][1]/scale)

    }

    context.stroke();
    context.restore();
}

function drawPlanetIcon(name) {
    context.save()
    context.translate(canvas.width/2, canvas.height/2)
    context.beginPath()
    context.fillStyle = planetSetup[name + "-" + typeMethod].color;

    context.arc(planetSetup[name + "-" + typeMethod].trajectory[planetSetup[name + "-" + typeMethod].time][0][0]/scale,
        planetSetup[name + "-" + typeMethod].trajectory[planetSetup[name + "-" + typeMethod].time][0][1]/scale,
        planetSetup[name + "-" + typeMethod].radius*2000000/scale,
        0, 2*Math.PI);
    context.fill()
    context.restore()


    if (name === "earth" && typeMethod === "eulerAsy") {
        context.save();
        let moonName = "moon-eulerAsy"
        context.translate(canvas.width/2, canvas.height/2)
        context.fillStyle = planetSetup[moonName].color;

        if (planetSetup[moonName].time > planetSetup[moonName].numberOfPoints-speed*2) {
            planetSetup[moonName].time = 1;
        }

        context.arc(planetSetup[moonName].trajectory[planetSetup[moonName].time][0][0]*55/scale + planetSetup[name + "-" + typeMethod].trajectory[planetSetup[name + "-" + typeMethod].time][0][0]/scale,
            planetSetup[moonName].trajectory[planetSetup[moonName].time][0][1]*55/scale + planetSetup[name + "-" + typeMethod].trajectory[planetSetup[name + "-" + typeMethod].time][0][1]/scale,
            planetSetup[moonName].radius*2000000/scale,
            0, 2*Math.PI);
        context.fill();
        context.restore()
        planetSetup[moonName].time+=speed;
    }

    planetSetup[name + "-" + typeMethod].time+=speed
}

function clearCanvas() {
    context.save();
    context.fillStyle = "#3D3D3D";
    context.beginPath();
    context.fillRect(0, 0, canvas.width, canvas.height)
    context.restore()
}


function drawEveryPlanet() {
    clearCanvas()
    drawSun()
    Object.keys(planetSetup).forEach(planet => {
        let name = planet.split("-")[0]
        if (planetSetup[planet]?.numberOfPoints !== 0 && planet.split("-")[1] === typeMethod && planet.split("-")[0] !== "moon") {
            if (!blacklistPlanet.includes(name)) {
                drawPlanetTrajectory(name)
                drawPlanetIcon(name);
            }
        }
    })
}

function createCheckbox(name) {
    let text = name.split("-");
    let li = document.createElement("li")

    li.innerHTML = `<input type="checkbox" name="planet" value="${text[0]}" id="${text[0]}" class="checkbox" checked> ${text[0]}`

    let div = document.getElementById("list");
    let range = document.getElementById("rangeLi")
    div.insertBefore(li, range);
}

function setAllCheckbox() {
    Object.keys(planetSetup).forEach(planet => {
        if (planetSetup[planet]?.trajectory && planet !== "moon-eulerAsy") {
            if (!document.getElementById(planet.split("-")[0])) {
                createCheckbox(planet);
            }
        }
    })
}

function init() {
    Object.keys(planetSetup).forEach(planetName => {
        planetSetup[planetName].trajectory = planetEulerAsy[planetName]
        if (planetEulerAsy[planetName]) {
            planetSetup[planetName].numberOfPoints = planetEulerAsy[planetName].length
        }
        else {
            planetSetup[planetName].numberOfPoints = 0
        }
    })

    Object.keys(planetEuler).forEach(planetName => {
        planetSetup[planetName].trajectory = planetEuler[planetName]
        if (planetEuler[planetName]) {
            planetSetup[planetName].numberOfPoints = planetEuler[planetName].length
        }
        else {
            planetSetup[planetName].numberOfPoints = 0
        }
    })

    setAllCheckbox();
}


function main() {
    init()
    console.log(planetSetup)
    setInterval(() => {
        drawEveryPlanet();
    }, 1);
}

main()

document.querySelector("#range").addEventListener("change", (input) => {
    rangeValue = parseInt(input.target.value, 10)
    speed = rangeValue
})

document.querySelector("#PPbutton").addEventListener("click", () => {
    speed = speed === 0 ? rangeValue : 0
})


document.querySelectorAll(".checkbox").forEach(checkbox => {
    if (!checkbox.checked) {
        blacklistPlanet.push(checkbox.id)
    }

    checkbox.addEventListener("change", (button) => {
        if (!button.target.checked) {
            if (!blacklistPlanet.includes(button.target.id)) {
                blacklistPlanet.push(button.target.id)
            }
        }
        else {
            if (blacklistPlanet.includes(button.target.id)) {
                blacklistPlanet = blacklistPlanet.filter(name => name !== button.target.id)
            }
        }
    })
})


canvas.addEventListener("wheel", (event) => {
    const delta = Math.sign(event.deltaY);
    if (delta > 0) {
        scale*=1.1
    }
    else {
        scale/=1.1
    }
})

canvas.addEventListener('click', (e) => {
    Object.entries(planetSetup).forEach(([key, value]) => {
        let planet2 = planetSetup[key]
        if (planet2.trajectory) {
            if (planet2.trajectory[value.time][0][0]/scale > e.offsetX-(canvas.width/2)-10 && planet2.trajectory[value.time][0][0]/scale < e.offsetX-(canvas.width/2)+10) {
                if (planet2.trajectory[value.time][0][1]/scale > e.offsetY-(canvas.height/2)-10 && planet2.trajectory[value.time][0][1]/scale < e.offsetY-(canvas.height/2)+10) {
                    let card = document.querySelector("#geo")
                    let actualCard = document.getElementById("card")
                    if (document.getElementById("card")) {
                        card.removeChild(actualCard);
                    }
                    let name = key.split("-")[0]
                    let planetCard = Card[name]
                    let htmlCard = document.createElement("div")
                    htmlCard.innerHTML = planetCard;

                    htmlCard.id = "card"
                    console.log(card)
                    card.appendChild(htmlCard);
                }
            }
        }
    })
})

document.querySelectorAll(".method").forEach(button => {
    button.addEventListener("click", () => {
        document.querySelectorAll(".method").forEach(euler => {
            euler.disabled = !euler.disabled
        })
        typeMethod = typeMethod === "eulerAsy" ? "euler" : "eulerAsy"
        document.querySelectorAll(".checkbox").forEach((checkbox) => {
            if (blacklistPlanet.includes(checkbox.id) && checkbox.checked) {
                blacklistPlanet = blacklistPlanet.filter(name => name !== checkbox.id)
            }
        })
    })
})
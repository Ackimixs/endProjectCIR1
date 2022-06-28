document.querySelectorAll("button").forEach(but => {
    but.addEventListener("click", (button) => {
        let p = document.querySelector(`#cont${button.target.id}`);
        if (p) {
            p.hidden = !p.hidden;
        }
    })
})
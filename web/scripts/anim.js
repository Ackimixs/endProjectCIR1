let toggle= document.querySelector('.toggle'); //permet de récupérer les toggle afin de pouvoir mettre en place des animations dessus
let body=document.querySelector('body');
let list=document.querySelector('.list');
toggle.addEventListener('click', function() {
    body.classList.toggle('open');
    list.hidden = !list.hidden
})   // permet d'ajouter une classe open lorsque l'on clique sur le toggle du menu et de l'enlever en recliquant, on sait donc si le menu est ouvert ou non grave à cette classe

const nameX = document.getElementById('user');
const doseX = document.getElementById('dose1');
const doseY = document.getElementById('dose2');
const timeX = document.getElementById('tame');
const sub = document.getElementById('Sub');
const del = document.getElementById('Del');

const db = firebase.database();

sub.addEventListener('click', (e) => {
    e.preventDefault();
    db.ref('/').set({
        NAME: nameX.value,
        C1: doseX.value,
        C2: doseY.value,
        TIME: timeX.value
    });
});

del.addEventListener('click', (e) => {
    e.preventDefault();
    db.ref('/').set(null);
});
// Create a function to change
// the hash value of the page
function changeLanguage(lang) {
    location.hash = lang;
    //location.reload();

    // Check if a hash value exists in the URL
    if (window.location.hash) {

        // Set the content of the webpage 
        // depending on the hash value
        if (window.location.hash == "#rus") {
            header.textContent = language.rus.welcome;
            nameLabel.innerHTML = language.rus.name;
            commentLabel.innerHTML = language.rus.comment;
            submitBtn.value = language.rus.submit;

            resume.innerHTML = language.rus.resume;
            resumeRus.innerHTML = language.rus.resumeRus;
            resumeEng.innerHTML = language.rus.resumeEng;
        }
        else if (window.location.hash == "#eng") {
            header.textContent = language.eng.welcome;
            nameLabel.innerHTML = language.eng.name;
            commentLabel.innerHTML = language.eng.comment;
            submitBtn.value = language.eng.submit;

            resume.innerHTML = language.eng.resume;
            resumeRus.innerHTML = language.eng.resumeRus;
            resumeEng.innerHTML = language.eng.resumeEng;
        }
    }
}

// Define the language reload anchors
var language = {
    rus: {
        welcome: "Привет мир!",
        name: "Имя",
        comment: "Сообщение",
        submit: "Отправить",
        resume: "Ссылка на резюме",
        resumeRus: "Рус",
        resumeEng: "Англ"
    },
    eng: {
        welcome: "Hi world!",
        name: "Name",
        comment: "Message",
        submit: "Submit",
        resume: "Resume link",
        resumeRus: "Rus",
        resumeEng: "Eng"
    },
};
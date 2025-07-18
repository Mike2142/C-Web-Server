
if (!document.__defineGetter__) {
    Object.defineProperty(document, 'cookie', {
        get: function () { return ''; },
        set: function () { return true; },
    });
} else {
    document.__defineGetter__("cookie", function () { return ''; });
    document.__defineSetter__("cookie", function () { });
}

let navRus = `<a href="#header">Вступление</a>
<a href="#headerC">Сервер</a>
<a href="#headerBack">Backend</a>
<a href="#headerFront">Frontend</a>
<a href="#headerForm">Сообщения</a>
<a href="#contacts">Контакты</a>`;

let navEng = `<a href="#header">Intro</a>
<a href="#headerC">Server</a>
<a href="#headerBack">Backend</a>
<a href="#headerFront">Frontend</a>
<a href="#headerForm">Messages</a>
<a href="#contacts">Contacts</a>`;

let headerCRus = "Сервер С";
let headerFrontRus = "Frontend разработка";
let headerBackRus = "Backend разработка";
let headerFormRus = "Форма сообщений";

let headerCEng = "Server in С";
let headerFrontEng = "Frontend development";
let headerBackEng = "Backend development";
let headerFormEng = "Message form";


let introRus = `Я - Михаил Колядин, инженер программного обеспечения и будущий архитектор ПО ). 
Это мой сайт-резюме, отправленный вам домашним сервером, написанном на языке C в августе 2022. 
Сервер использует только стандартные библиотеки пакета GCC.`;
let aboutMeRus = `Обо мне: люблю спорт, программирование, коммандную работу и самореализацию
Чему я учусь: архитектура компьютера, сети, язык C
Подробное резюме: <a id="resumeRus" href="https://drive.google.com/file/d/1k5UUy1Xt8HiYsvXqLmvcXGEnmrsIP9Dg/view?usp=sharing" target="_blank">Рус</a>/<a id="resumeEng" href="https://drive.google.com/file/d/1ygn1ZqbZa7yCTB44Cve_eqtzwRBoOHR4/view?usp=sharing" target="_blank">Англ</a>
`;
let lookoutRus = `Проект, который я ищу
- предпочтительный стэк: C/C#/.Net, Java/Spring
- предпочтительная область: телеком, сети`;
let contactsRus = `Спасибо за ваше внимание! 
Буду рад обсудить любые идеи и предложения:
почта 2surfingbirds@gmail.com
telegram <a href="https://t.me/MikeFlow108" target="_blank">@MikeFlow108</a>
whatsapp <a href="https://wa.me/79265265663" target="_blank">ссылка</a>
`;

let introEng = `I’m Mike Kolyadin, a software engineer and wannabe software architect.
This is my resume-page, sent to you by home-server coded in C language in August 2022.
This server utilizes only the standard GCC libraries.`;
let aboutMeEng = `About me: love for sports, programming, teamwork and self-realization
My everyday studies: computer architecture, networks, c language
Detailed resume: <a id="resumeRus" href="https://drive.google.com/file/d/1k5UUy1Xt8HiYsvXqLmvcXGEnmrsIP9Dg/view?usp=sharing" target="_blank">Rus</a>/<a id="resumeEng" href="https://drive.google.com/file/d/1ygn1ZqbZa7yCTB44Cve_eqtzwRBoOHR4/view?usp=sharing" target="_blank">Eng</a>
`;
let lookoutEng = `Next project lookout
- preferable stacks: C/C#/.Net/ , Java/Spring
- preferable field: telecom, networks`;
let contactsEng = `Thanks for your attention! 
Please, feel free to reach out:
email 2surfingbirds@gmail.com
telegram <a href="https://t.me/MikeFlow108" target="_blank">@MikeFlow108</a>
whatsapp <a href="https://wa.me/79265265663" target="_blank">link</a>
`;


let serverRus = `Возможности
- HTTP, парсинг запросов
- HTTP, создание ответов
- Отправка файлов
- LRU кэш файлов
    - хэш таблица и связанный список
    - срок годности кэш-файлов
- Многопоточность (pthread.h), блокировка файлов и чистка памяти
- Сообщения, парсинг UTF-8 и обогащение

Страницы
- <a href="/index.html" target="_blank">/index.html</a>
    - также открывается в <a href="/" target="_blank">корне сайта /</a>
    - <a href="#headerForm">форма сообщений</a>
- <a href="/comments.html" target="_blank">/comments.html</a>, база сообщений
- <a href="/d20" target="_blank">/d20</a> api, генерирует случайное число 0-20
- <a href="/myip" target="_blank">/myip</a> api, отправляет ip адрес пользователя

исходный код <a href="https://github.com/Mike2142/C-Web-Server/tree/mkolyadin" target="_blank">ссылка</a>
основа проекта <a href="https://github.com/bloominstituteoftechnology/C-Web-Server" target="_blank">ссылка</a>
`;

let serverEng = `Capabilities
- HTTP, request parser
- HTTP, response builder
- File serving
- LRU file cache
    - hash table and double-linked list
    - cache files expiration
- Multithreading (pthread.h), file blocking and cleanup handler
- Messaging, UTF-8 decoding and message enrichment

Site pages
- <a href="/index.html" target="_blank">/index.html</a>
    - opens as <a href="/" target="_blank">root /</a>
    - <a href="#headerForm" >message form</a>
- <a href="/comments.html" target="_blank">/comments.html</a>, message base
- <a href="/d20" target="_blank">/d20</a> api, generates random number
- <a href="/myip" target="_blank">/myip</a> api, sends user's IP

source code <a href="https://github.com/Mike2142/C-Web-Server/tree/mkolyadin" target="_blank">link</a>
based on <a href="https://github.com/bloominstituteoftechnology/C-Web-Server" target="_blank">link</a>
`;


let backendToolsRus = `Backend инструменты
- C
- Python, Django
- SQL, PostGre, OracleDB, MySQL
- Unix systems, Windows 10, Docker
- IBM Software, Omnibus, Jazz
- и подобные`;
let backendCommRus = `Backend, коммерческие проекты
- проекты по насыщению данных от систем и пользователя, наполнение базы данных, передача потока следующему приложению
- сбор писем из ящиков MS Exchange, парсинг содержания и создание записей/аварий в системе IBM Fault Management
- backend для интерактивной карты сети, со статистикой аварий. кэширование и преобразования данных между базами, 
  вычисление статистики по городам и регионам, общие суммы. круглосуточная трансляция на видеостене заказчика. `;
let backendTrainRus = `Backend, <a href="https://github.com/Mike2142/cs50web" target="_blank">учебные проекты</a> (2020)`;


let backendToolsEng = `Backend tools
- C
- Python, Django
- SQL, PostGre, OracleDB, MySQL
- Unix systems, Windows 10, Docker
- IBM Software, Omnibus, Jazz
- etc.`;
let backendCommEng = `Backend, commercial projects
- various projects for enriching data with info collected from other systems and from user input, 
  and sending it further to db or next backend app
- service to read emails from MS Exchange, parse them and generate alerts to IBM Fault Management system
- statistics map (backend), fetching and calculating realtime equipment statistics, by city, region or sum. 
  for further rendering on schematic country map, shown on wall-mounted tv-panels`;
let backendTrainEng = `Backend, <a href="https://github.com/Mike2142/cs50web" target="_blank">training projects</a> (2020)`;


let frontendToolsRus = `Frontend инструменты
- JavaScript, RxJs, Angular
- CSS, SCSS, SASS, Less, Stylus
- HTML, Nunjucks
- npm, и другие`;
let frontendCommRus = `Frontend, коммерческие проекты
- spa приложение, меню и формы для парсинга и обогащения сетевых аварий, 
  отправка данных для дальнейшего использования
- географическая карта сети
    - отображние данных в реальном времени 
    - точки установки оборудования
    - интерактивная таблица аварий
    - навигация по карте, вручную и переход к аварии из таблицы
    - разработано для круглосуточной трансляции на видео-панелях
- карта статистика сети, состояние оборудования в реальном времени, общие данные по городам, регионам и суммам. 
  визуализация на схематической карте страны, трансляция на видео-панели
- spa приложение. Интерактивные графики по трафику, ошибкам и состоянию оборудования. 
- SaaS платформа, SEO оптимизация сайтов`;
let frontendTrainRus = `Frontend, <a href="https://github.com/Mike2142/Demo" target="_blank">учебные проекты</a> (2019)`;


let frontendToolsEng = `Frontend tools
- JavaScript, RxJs, Angular
- CSS, SCSS, SASS, Less, Stylus
- HTML, Nunjucks
- npm, etc.`;
let frontendCommEng = `Frontend, commercial projects
- spa, browser menus and forms for parsing and enriching network alerts, and sending them for further usage
- gis map
    - realtime data 
    - equipment locations
    - interactive alerts table
    - map navigation
    - developed for realtime monitoring on wall-mounted tv-panels
- statistics-map (frontend), realtime equipment statistics, shown by city, region or sum. 
  rendered on schematic country map and shown on wall-mounted tv-panels
- spa, charts interfaces (2 projects), equipment statistics monitoring, interactive charts and equipment data
- SaaS platform for SEO optimization`;
let frontendTrainEng = `Frontend, <a href="https://github.com/Mike2142/Demo" target="_blank">training projects</a> (2019)`;


// Define the language reload anchors
var language = {
    rus: {
        nav: navRus,

        header: "Привет мир!",
        headerC: headerCRus,
        headerBack: headerBackRus,
        headerFront: headerFrontRus,
        headerForm: headerFormRus,

        name: "Имя",
        comment: "Сообщение",
        submit: "Отправить",
        resumeRus: "Рус",
        resumeEng: "Англ",

        intro: introRus,
        aboutMe: aboutMeRus,
        lookout: lookoutRus,
        contacts: contactsRus,

        server: serverRus,
        backendTools: backendToolsRus,
        backendComm: backendCommRus,
        backendTrain: backendTrainRus,

        frontendTools: frontendToolsRus,
        frontendComm: frontendCommRus,
        frontendTrain: frontendTrainRus,
    },
    eng: {
        nav: navEng,

        header: "Hi world!",
        headerC: headerCEng,
        headerBack: headerBackEng,
        headerFront: headerFrontEng,
        headerForm: headerFormEng,

        name: "Name",
        comment: "Message",
        submit: "Submit",
        resumeRus: "Rus",
        resumeEng: "Eng",

        intro: introEng,
        aboutMe: aboutMeEng,
        lookout: lookoutEng,
        contacts: contactsEng,

        server: serverEng,
        backendTools: backendToolsEng,
        backendComm: backendCommEng,
        backendTrain: backendTrainEng,

        frontendTools: frontendToolsEng,
        frontendComm: frontendCommEng,
        frontendTrain: frontendTrainEng,
    },
};


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
            header.textContent = language.rus.header;
            headerC.textContent = language.rus.headerC;
            headerBack.textContent = language.rus.headerBack;
            headerFront.textContent = language.rus.headerFront;
            headerForm.textContent = language.rus.headerForm;

            nameLabel.innerHTML = language.rus.name;
            commentLabel.innerHTML = language.rus.comment;
            submitBtn.value = language.rus.submit;

            intro.innerHTML = language.rus.intro;
            aboutMe.innerHTML = language.rus.aboutMe;
            lookout.innerHTML = language.rus.lookout;
            contacts.innerHTML = language.rus.contacts;

            server.innerHTML = language.rus.server;
            backendTools.innerHTML = language.rus.backendTools;
            backendComm.innerHTML = language.rus.backendComm;
            backendTrain.innerHTML = language.rus.backendTrain;

            frontendTools.innerHTML = language.rus.frontendTools;
            frontendComm.innerHTML = language.rus.frontendComm;
            frontendTrain.innerHTML = language.rus.frontendTrain;

            nav.innerHTML = language.rus.nav;
        }
        else if (window.location.hash == "#eng") {
            header.textContent = language.eng.header;
            headerC.textContent = language.eng.headerC;
            headerBack.textContent = language.eng.headerBack;
            headerFront.textContent = language.eng.headerFront;
            headerForm.textContent = language.eng.headerForm;

            nameLabel.innerHTML = language.eng.name;
            commentLabel.innerHTML = language.eng.comment;
            submitBtn.value = language.eng.submit;

            intro.innerHTML = language.eng.intro;
            aboutMe.innerHTML = language.eng.aboutMe;
            lookout.innerHTML = language.eng.lookout;
            contacts.innerHTML = language.eng.contacts;

            server.innerHTML = language.eng.server;
            backendTools.innerHTML = language.eng.backendTools;
            backendComm.innerHTML = language.eng.backendComm;
            backendTrain.innerHTML = language.eng.backendTrain;


            frontendTools.innerHTML = language.eng.frontendTools;
            frontendComm.innerHTML = language.eng.frontendComm;
            frontendTrain.innerHTML = language.eng.frontendTrain;

            nav.innerHTML = language.eng.nav;
        }
    }
}

if (window.location.hash) {
    let initLang = window.location.hash;
    let inL = initLang.slice(1);
    changeLanguage(inL);
}
![PROJECT_PHOTO](https://github.com/AlexGyver/microPong/blob/master/proj_img.jpg)
# Микро консоль с игрой Pong
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
- Миниатюрная игровая приставка с игрой Pong, построенная на ATtiny85 и OLED дисплее
- Страница проекта на сайте: https://alexgyver.ru/microPong/

<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **firmware** - прошивки для Arduino
- **schemes** - схемы подключения компонентов

<a id="chapter-2"></a>
## Схемы
![SCHEME](https://github.com/AlexGyver/microPong/blob/master/schemes/scheme1.jpg)
![SCHEME](https://github.com/AlexGyver/microPong/blob/master/schemes/scheme3.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
* ATtiny85 https://www.chipdip.ru/product/attiny85-20pu
* ATtiny85 али http://ali.ski/BG9nB  http://ali.ski/87pQX6
* Кнопки http://ali.ski/2WLyAi
* OLED 128x32 http://ali.ski/uVN_XR
* USBASP http://ali.ski/qZQ8iF
* Макетка http://ali.ski/QKOyi
* Проводочки http://ali.ski/_WrhlQ  http://ali.ski/scOeX
* Бат. отсек http://ali.ski/HBbYm


## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* **Подключить внешнее питание 5 Вольт**
* Подключить плату к компьютеру
* Файл/Настройки, вставить ссылку http://drazzy.com/package_drazzy.com_index.json в текст-бокс для дополнительных ссылок для менеджера плат
* Открыть Инструменты/Плата/Менеджер плат…, найти ATTinyCore by Spence Konde, установить актуальную версию
* Открыть Инструменты/Плата/ATtiny25/45/85
* Инструменты/Программатор/USBASP (или чем вы будете шить)
* Инструменты/Записать загрузчик
* Загрузить прошивку (Скетч/Загрузить через программатор)


## Настройки в коде
    GAME_SPEED 100    // стандартный период движения шарика
    II_SPEED 250      // стандартный период движения противника
    RANDOM_BOUNCE 1   // отбивать шарик в случайном направлении
	
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)
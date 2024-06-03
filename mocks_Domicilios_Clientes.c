#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domicilios.h"
#include "clientes.h"

//struct CLIENTES RANDOM

int getNroCliente(){
    return (rand()%1000)+1;
}

char* getNombres()
{
    char* nombre = (char*) malloc(sizeof(char)*60);
    char nombres[][30]= {"Juan","Apolonio","Tulio","Maria","Violeta","Amalio","Juan","Roberto","Antonio","Pedro","Fernando","Jacinto","Anibal","Antonio","Atalayo",
                         "Bertino","Anastasio","Amor","Arturo","Diego","Mario","Tamaro","Adolfo","Alfonso","Pedro","Alfredo","Rolando","Mauro","Amancio","Benicio","Bertin","Ildefonso","Amilcar","Cuchuflito","Jazmino",
                         "Charles", "Aristóteles", "Napoleón", "Julio", "Marie", "Albert", "Santiago", "Mateo", "Sofía", "Sebastián", "María José", "Leonardo", "Valentina",
                         "Harry", "Hermione", "Ron", "Draco", "Albus", "Severus", "Sirius", "Remus", "Minerva", "Rubeus", "Dolores", "Bellatrix", "Lucius", "Neville", "Luna", "Ginny", "Fred",
                         "George", "Percy", "Bill", "Charlie", "Arthur", "Molly", "Fleur", "Viktor", "Cedric", "Cho", "Oliver", "James", "Lily", "Peter", "Tom", "Vernon", "Petunia", "Dudley","Luke",
                         "Leia", "Han", "Chewbacca", "Darth", "Anakin", "Padmé", "Obi-Wan", "Yoda", "Mace", "Qui-Gon", "Jar Jar", "Lando", "Boba", "Jango", "Finn", "Rey", "Poe", "Kylo", "BB-8", "R2-D2", "C-3PO", "Palpatine",
                         "Grievous", "Dooku", "Maul", "Wicket", "Jabba", "Ewok", "Wookiee", "Stormtrooper", "Clone Trooper","Caesar", "Claudius", "Portia", "Octavia", "Flavius", "Venia", "Buttercup",
                         "Katniss", "Peeta", "Gale", "Haymitch", "Effie", "Cinna", "Primrose", "Rue", "Cato", "Clove", "Foxface", "Thresh", "Glimmer", "Marvel", "President Snow", "Seneca",
                         "Bella", "Edward", "Jacob", "Charlie", "Renee", "Carlisle", "Esme", "Alice", "Jasper", "Rosalie", "Emmett", "Jessica", "Angela", "Mike", "Eric", "Tyler", "Lauren", "Billy", "Sam", "Emily", "Paul",
                         "Jared", "Embry", "Quil", "Seth", "Leah", "Victoria", "James", "Laurent", "Jane", "Alec", "Aro", "Marcus", "Caius","Jon", "Daenerys", "Tyrion", "Cersei", "Jaime", "Arya", "Sansa", "Bran", "Ned", "Catelyn",
                         "Robb", "Rickon", "Theon", "Yara", "Euron", "Balon", "Davos", "Melisandre", "Stannis", "Renly", "Robert", "Joffrey", "Tommen", "Myrcella", "Margaery", "Loras", "Olenna", "Tywin", "Kevan", "Lancel", "Gregor", "Sandor", "Brienne",
                         "Podrick", "Bronn", "Varys", "Petyr", "Samwell", "Gilly", "Tormund", "Ygritte", "Mance", "Jeor", "Edd", "Gendry", "Beric", "Thoros", "Melisandre", "Missandei", "Grey Worm", "Jorah", "Daario", "Hodor", "Meera", "Jojen", "Osha",
                         "Ramsay", "Roose", "Walder", "Edmure", "Catelyn", "Lysa", "Robin", "Oberyn", "Ellaria", "Doran", "Trystane", "Tyene", "Nymeria", "Obara", "Qyburn", "Night King",
                         "Moises", "Monaco", "Mongore", "Monsalvo", "Monseñor", "Monseñor", "Monseñor", "Monte", "Montecarlo", "Montes", "Monteverde", "Mrina", "Namuncura", "Napoles", "Necochea",
                         "Nestor", "Neuquen", "Nicolas", "Nicolas", "Nork", "Nuestra", "Nuevo", "Olegario", "Olegario", "Olleros", "Ombu", "Onesimo", "Adolfo", "Aeropuerto", "Agua", "Agustin",
                         "Albeniz", "Alberdi", "Albert", "Alberto", "Alejandro", "Alejandro", "Alexander", "Alfonsina", "Almafuerte", "Almirante", "Almonacid", "Alvarez", "Amadeo", "Ambrosio", "Andrea",
                         "Andres", "Angel", "Angel", "Antartida", "Antonio", "Antonio", "Antonio", "Antonio", "Antonio", "Antonio", "Antonio", "Antonio", "Antonio", "Antonio", "Arabe", "Arabe", "Aragon", "Araoz",
                         "Ariel", "Aristobulo", "Armenia", "Arribeños", "Arturo", "Arturo", "Arturo", "Asturias", "Atahualpa", "Augusto", "Augustus", "Aviadora", "Ayacucho", "Azopardo", "Bahia", "Bahia", "Bahia",
                         "Baldomero", "Bartolome", "Bathurst", "Bautista", "Beethoven", "Belgica", "Belisario", "Bellini", "Benito", "Benito", "Benjamin", "Bermejo", "Berna", "Bernardino", "Bernardo", "Bernardo",
                         "Biarritz", "Blas", "Bolivia", "Bosque", "Brasil", "Bristol", "Bruselas", "Buenos", "Cabo", "Calabrese", "Calabria", "Calfucura", "Campana", "Canada", "Carballo", "Carlos", "Carlos",
                         "Carmen", "Carrasco", "Caseros", "Casildo", "Castellamar", "Castelli", "Castex", "Castilla", "Catalina", "Cataluña", "Catamarca", "Catedral", "Caupolican", "Cayetano", "Cayetano", "Cedro",
                         "Ceferino", "Celso", "Centenario", "Central", "Cerrito", "Cesar", "Chacabuco", "Chaco", "Chara", "Charlone", "Chile", "Chubut", "Ciancheta", "Ciudad", "Ciudad", "Ciudad", "Ciudad", "Cohelo",
                         "Coliqueo", "Colombia", "Comandante", "Comdoro", "Comunidad", "Concepcion", "Constitucion", "Conte", "Copacabana", "Corbeta", "Cordoba",
                         "Cornelio", "Coronel","Remilgo","Aragorn", "Bardo el arquero", "Beorn", "Beren", "Boromir", "Arwen", "Legolas", "Galadriel", "Frodo", "Pippin", "Merry", "Sam", "Gimli", "Gandalf", "Bárbol",
                         "Ross", "Rachel", "Chandler", "Monica", "Joey", "Phoebe"
                        };
    //strcpy(nombre,nombres[rand()%(sizeof(nombres)/30)]);
    //sprintf(nombre, "%s %s", nombres[rand()%(sizeof(nombre)/30)], nombres[rand()%(sizeof(nombres)/30)]);///
    sprintf(nombre, "%s %s", nombres[rand()%(sizeof(nombres)/sizeof(nombres[0]))], nombres[rand()%(sizeof(nombres)/sizeof(nombres[0]))]);

    return nombre;
}

char* getApellido()
{
    char* apellido = (char*) malloc(sizeof(char)*30);
    char apellidos[][30]= {"Fernandez","Gomez","Vlick","Argento","Molina","Gomez","Perez","Rodriguez","Latorre","Fernandez","Torquemada", "Marijuan", "Roca", "Mitre", "Rivadavia",
                           "San Martin", "Alvarez", "Comizo", "Borges", "Zama", "Recato", "Olvido", "Gil", "Trapero", "Restinga",
                           "De´Antonio", "Ramirez", "Spinetta", "Cortez", "Gonzalez", "Andujar", "SanJuan", "Bautista", "Anchorena", "Paso",
                           "Gaboto","Vega","Vargas","Lloret","Linares","Suarez","Sierra","Amenabar","Blanco","White","Black","Smith", "Johnson", "Williams", "Brown",
                           "Darwin", "Aristóteles", "Bonaparte", "César", "Curie", "Einstein", "Shakespeare", "Picasso", "Windsor", "Habsburgo", "Medici", "Sajonia-Coburgo-Gotha",
                           "Churchill", "Kennedy", "Lincoln", "Washington", "Roosevelt", "Nixon", "Reagan", "Obama", "Trump", "Biden", "Gandhi", "Nehru", "Mandela", "Tutankhamun",
                           "Cleopatra", "Alexander", "Attila", "Charlemagne", "Joan of Arc", "Napoleon", "Victoria", "Elizabeth", "Churchill", "Hitler", "Stalin", "Mao", "Guevara", "Castro",
                           "Gorbachev", "Putin", "Gandhi", "Nehru", "Mandela", "Tutankhamun", "Cleopatra", "Alexander", "Attila", "Charlemagne", "Joan of Arc", "Napoleon", "Victoria",
                           "Elizabeth", "Churchill", "Hitler", "Stalin", "Mao", "Guevara", "Castro", "Gorbachev", "Putin", "Gandhi", "Nehru", "Mandela",
                           "Jones", "García", "Miller", "Davis", "Rodríguez", "Martínez", "Hernández", "López", "González", "Pérez", "Wilson", "Anderson", "Thomas", "Taylor",
                           "Moore", "Jackson", "Martin", "Lee", "Pérez", "Thompson", "White", "Harris", "Sánchez", "Clark", "Ramírez", "Lewis", "Robinson", "Walker", "Young",
                           "Allen", "King", "Wright", "Scott", "Torres", "Nguyen", "Hill", "Flores", "Green", "Adams", "Nelson", "Baker", "Hall", "Rivera", "Campbell", "Mitchell", "Carter", "Roberts",
                           "Baggins", "Brandybuck", "Took", "Gamgee", "Gandalf", "Aragorn", "Legolas", "Gimli", "Boromir", "Frodo", "Samwise", "Peregrin", "Meriadoc", "Bilbo", "Sauron", "Saruman", "Gollum",
                           "Elrond", "Galadriel", "Arwen", "Eowyn", "Faramir", "Theoden", "Eomer", "Treebeard", "Shelob", "Witch-king", "Balrog", "Denethor", "Celeborn",
                           "Potter", "Weasley", "Granger", "Malfoy", "Dumbledore", "Snape", "Voldemort", "Black", "Lupin", "Moody", "Hagrid", "Diggory", "Longbottom", "Lovegood",
                           "Scamander", "Krum", "Dursley", "Umbridge", "McGonagall", "Flitwick", "Sprout", "Slughorn", "Lockhart", "Quirrell", "Trelawney", "Filch", "Peeves", "Nearly Headless Nick",
                           "Moaning Myrtle", "Dobby", "Winky", "Kreacher", "Hedwig", "Fawkes", "Norbert", "Aragog", "Buckbeak"
                           "Skywalker", "Solo", "Organa", "Kenobi", "Yoda", "Vader", "Palpatine", "Fett", "Grievous", "Dooku", "Maul", "Windu", "Qui-Gon", "Padmé", "Anakin", "Leia", "Luke", "Han", "Chewbacca",
                           "R2-D2", "C-3PO", "Lando", "Ewok", "Jabba", "Wookiee", "Stormtrooper", "Trooper", "Boba", "Jango", "JarJar", "Gungan", "Tusken", "People", "Jawa",
                           "White", "Pinkman", "Ehrmantraut", "Goodman", "Schrader", "Salamanca", "Fring","Soprano", "Moltisanti", "Aprile", "Baccalieri", "Blundetto", "Bonpensiero", "Cifaretto",
                           "Gualtieri", "LaRocca", "Makazian", "Palmice", "Scatino", "Spatafore", "Draper", "Olson", "Campbell", "Sterling", "Harris", "Pryce", "Romano", "Cosgrove", "Crane", "Francis",
                           "Little", "Moreland", "McNulty", "Greggs", "Freamon", "Daniels", "Bell", "Barksdale", "Sobotka", "Carver", "Herc", "Scott", "Halpert", "Beesly", "Schrute", "Flenderson", "Vance",
                           "Palmer", "Martin", "Bernard", "Kapoor", "Bratton","Stark", "Lannister", "Targaryen", "Baratheon", "Greyjoy", "Bolton", "Tyrell", "Martell", "Tully", "Arryn", "Tarly", "Mormont",
                           "Seaworth", "Clegane","Byers", "Wheeler", "Hopper", "Harrington", "Sinclair", "Mayfield", "Henderson", "Driscoll", "Kline", "Brenner","Geller", "Green", "Bing", "Buffay", "Tribbiani",
                           "Simpson", "Bouvier", "Flanders", "Burns", "Smithers", "Szyslak", "Wiggum", "Krustofsky", "VanHouten", "Hibbert","Hofstadter", "Cooper", "Koothrappali", "Wolowitz", "Fowler", "Farrah", "Rostenkowski"
                          };
    strcpy(apellido, apellidos[rand()%(sizeof(apellidos)/30)]);
    return apellido;
}

char* getDnis()
{
    char* dni = (char*) malloc(sizeof(char)*6);
    sprintf(dni, "%d", (rand()%30000001)+20000000);
    return dni;
}

char* getEmail() {

    char* email = (char*) malloc(sizeof(char)*30);
    char dominios[][30] = {"gmail.com", "yahoo.com", "live.com", "hotmail.com", "outlook.com"};

    char* apellido = getApellido();
    int randomDominioIndex = rand() % (sizeof(dominios) / sizeof(dominios[0]));

    sprintf(email, "%s@%s",apellido, dominios[randomDominioIndex]);

    free(apellido);

    return email;
}
char* getTelefono()
{
    char* telefono = (char*) malloc(sizeof(char)*14);
    sprintf(telefono, "223%d", (rand()%9000000)+1000000);
    return telefono;
}

stCliente getClienteRandom()
{
    stCliente c;

    c.nroCliente= getNroCliente();

    strcpy(c.nombre,getNombres());

    strcpy(c.apellido,getApellido());

    strcpy(c.dni,getDnis());

    strcpy(c.email,getEmail());

    strcpy (c.telefono, getTelefono());

    return c;
}

///struct DOMICILIOS RANDOM

char* getCalles()
{
    char* calle = (char*) malloc(sizeof(char)*30);
    char calles[][30]= {"Alfonsina Storni", "Almafuerte", "Brown", "Almonacid", "Alvarez Condarco", "Amadeo Courel", "Ambrosio Bestoso", "Andrea C", "Andrea Doria", "Andres Mac Gaul", "Angel Pacheco",
                        "Angel Roffo", "Antartida Argentina", "Antonio Alice", "Antonio Alvarez", "Antonio Baron de Marchi", "Antonio Galeano", "Antonio Garagiola", "Antonio Gregorio Balcarce", "Antonio Luis Berutti",
                        "Antonio Maria Gianelli", "Antonio Maria Saenz", "Antonio Martinez", "Antonio Pujia", "Antonio Tapia", "Antonio Valentini", "Arabe Siria", "Arabe Unida", "Aragon", "Araoz de Lamadrid", "Ariel V Manuwal",
                        "Aristobulo del Valle", "Armenia", "Arribeños", "Arturo Alio", "Arturo Della Paolera", "Arturo Jauretche", "Asturias", "Atahualpa", "Augusto Sandino", "Augustus", "Aviadora Carola Lorenzini", "Ayacucho",
                        "Azopardo", "Alvarez Condarco", "Amadeo Courel", "Ambrosio Bestoso", "Andrea C", "Andrea Doria", "Andres Mac Gaul", "Angel Pacheco", "Angel Roffo", "Antartida Argentina", "Antonio Alice", "Antonio Alvarez",
                        "Antonio Baron de Marchi", "Antonio Galeano", "Antonio Garagiola", "Antonio Gregorio Balcarce", "Antonio Luis Berutti", "Antonio Maria Gianelli", "Antonio Maria Saenz", "Antonio Martinez", "Antonio Pujia",
                        "Antonio Tapia", "Antonio Valentini", "Arabe Siria", "Arabe Unida", "Aragon", "Araoz de Lamadrid", "Ariel V Manuwal", "Aristobulo del Valle", "Armenia", "Arribeños", "Arturo Alio", "Arturo Della Paolera",
                        "Arturo Jauretche", "Asturias", "Atahualpa", "Augusto Sandino", "Augustus", "Aviadora Carola Lorenzini", "Ayacucho", "Azopardo", "Agustin Magaldi", "Agustin Rodriguez", "Albeniz", "Alberdi", "Albert Einstein",
                        "Alberto R Mascias", "Alejandro Korn", "Alejandro Maria de Aguado", "Alexander Fleming","Bahia Aguirre", "Bahia Blanca", "Bahia Thetis", "Baldomero", "Bartolome Mitre", "Bathurst", "Bautista Mendioroz", "Beethoven",
                        "Belgica", "Belisario Roldan", "Bellini", "Benito Juarez", "Benito Lynch", "Benjamin Matienzo", "Bermejo", "Berna", "Bernardino Rivadavia", "Bernardo de Irigoyen", "Bernardo Houssay", "Bernardo O Higgins", "Biarritz",
                        "Blas Parera", "Bolivia", "Bosque Grande", "Brasil", "Bristol", "Bruselas", "Buenos Aires", "Martin", "Ramirez", "Russell", "Cabo Corrientes", "Cabo Gabito Banat", "Calabrese", "Calabria", "Calfucura", "Campana",
                        "Canada", "Carballo", "Carlos Chapeaurouge", "Carlos Gardel", "Carlos Maria Alvear", "Carlos Pellegrini", "Carlos Tejedor", "Carmen de Las Flores", "Carrasco", "Caseros", "Casildo Villar", "Castellamar", "Castelli", "Castex",
                        "Castilla y Leon", "Catalina Daprotis", "Cataluña", "Catamarca", "Catedral", "Caupolican", "Cayetano Daglio", "Cayetano", "Cedro Azul", "Ceferino Namuncura", "Celso Aldao", "Centenario", "Central", "Cerrito",
                        "Cesar Gascon", "Chacabuco", "Chaco", "Chara", "Charlone", "Chile", "Chubut", "Ciancheta", "Ciudad de Asuncion", "Ciudad de Bragado", "Ciudad de Dolores", "Ciudad de Rosario", "Cohelo de Meyrelles", "Coliqueo", "Colombia",
                        "Comandante Luis Piedrabuena", "Espora", "Comdoro", "Comodoro", "Pedro Luis", "Foral de Navarra", "Concepcion Arenal", "Constitucion", "Conte Biancamano", "Conte Grand",
                        "Copacabana", "Corbeta", "Cordoba", "Cornelio Saavedra", "Leonardo Rosales", "Bautista Azopardo", "Pringles", "Luis Cabassa", "Martinez de Hoz"
                         };
    strcpy(calle,calles[rand()%(sizeof(calles)/30)]);
    return calle;
}

char* getNumero()
{
    char* numero = (char*) malloc(sizeof(char)*6);
    sprintf(numero, "%d", (rand()%100000)+1);
    return numero;
}

char* getLocalidades()
{
    char* localidad = (char*) malloc(sizeof(char)*50);
    char localidades [][50]= {"Adolfo Alsina", "Adolfo Gonzales Chaves", "Alberti", "Almirante Brown", "Arrecifes", "Avellaneda", "Ayacucho", "Azul", "Bahía Blanca", "Balcarce", "Baradero", "Benito Juárez", "Berazategui", "Berisso", "Bolívar", "Bragado", "Brandsen", "Campana",
                              "Cañuelas", "Capitán Sarmiento", "Carlos Casares", "Carlos Tejedor", "Carmen de Areco", "Castelli", "Chacabuco", "Chascomús", "Chivilcoy", "Colón", "Coronel de Marina Leonardo Rosales", "Coronel Dorrego", "Coronel Pringles", "Coronel Suárez", "Daireaux",
                              "Dolores", "Ensenada", "Escobar", "Esteban Echeverría", "Exaltación de la Cruz", "Ezeiza", "Florencio Varela", "Florentino Ameghino", "General Alvarado", "General Alvear", "General Arenales", "General Belgrano", "General Guido", "General Juan Madariaga",
                              "General La Madrid", "General Las Heras", "General Lavalle", "General Paz", "General Pinto", "General Pueyrredón", "General Rodríguez", "General San Martín", "General Viamonte", "General Villegas", "Guaminí", "Hipólito Yrigoyen", "Hurlingham", "Ituzaingó",
                              "José C. Paz", "Junín", "La Costa", "La Matanza", "Lanús", "La Plata", "Laprida", "Las Flores", "Leandro N. Alem", "Lezama", "Lomas de Zamora", "Luján", "Magdalena", "Maipú", "Malvinas Argentinas", "Mar Chiquita", "Marcos Paz", "Mercedes", "Merlo", "Monte",
                              "Monte Hermoso", "Moreno", "Moron", "Navarro", "Necochea", "Nueve de Julio", "Olavarría", "Patagones", "Pehuajó", "Pellegrini", "Pergamino", "Pila", "Pilar", "Pinamar", "Presidente Perón", "Puán", "Punta Indio", "Quilmes", "Ramallo", "Rauch", "Rivadavia",
                              "Rojas", "Roque Pérez", "Saavedra", "Saladillo", "Salliqueló", "Salto", "San Andrés de Giles", "San Antonio de Areco", "San Cayetano", "San Fernando", "San Isidro", "San Miguel", "San Nicolás", "San Pedro", "San Vicente", "Suipacha", "Tandil", "Tapalqué",
                              "Tigre", "Tordillo", "Tornquist", "Trenque Lauquen", "Tres Arroyos", "Tres de Febrero", "Tres Lomas", "Veinticinco de Mayo", "Vicente López", "Villa Gesell", "Villarino", "Zárate"};
    strcpy(localidad,localidades[rand()%(sizeof(localidades)/50)]);
    return localidad;
}
char* getProvincias()
{
    char* provincia = (char*) malloc(sizeof(char)*40);
    char provincias[][40]= {"Buenos Aires", "Catamarca", "Chaco", "Chubut", "Córdoba", "Corrientes", "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones", "Neuquén", "Río Negro", "Salta",
                            "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tierra del Fuego, Antártida", "Tucumán"};
    strcpy(provincia,provincias[rand()%(sizeof(provincias)/40)]);
    return provincia;
}

char* getCpos()
{
    char* cpos = (char*) malloc(sizeof(char)*6);  // no excederá los 5 dígitos
    sprintf(cpos, "%d", (rand()%100000)+1);
    return cpos;
}

stDomicilio getDomicilioRandom()
{
    stDomicilio d;

    getCalles(d.calle);
    strcpy(d.calle,getCalles());

    getNumero(d.nro);
    strcpy(d.nro,getNumero());

    getLocalidades(d.localidad);
    strcpy(d.localidad,getLocalidades());

    getProvincias(d.provincia);
    strcpy(d.provincia,getProvincias());

    getCpos(d.cpos);
    strcpy (d.cpos, getCpos());

    return d;
}

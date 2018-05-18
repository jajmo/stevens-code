(function () {
    // All browser based JavaScript is run in the global scope. This means that we should use 
    // IIFEs in order to self-contain our logic and avoid collisions. 
    // We will learn how to export code properly soon

    // Updating this will cause updates to appear on the page!
    var biographyPageOptions = {
        name: "Phil Barresi",
        hobby: "Making Coffee",
        favoriteVegetable: "Brussel Sprouts", // Seriously
        favoriteProgrammingLanguage: "JavaScript", // obviously
        currentProject: "w2p",
        currentProjectDescription: "w2p is a worker-to-promise library that will allow you to call functions on web workers, and use the results as promises!"
    };
    
    // We can store references to elements in variables! 
    // We use the DOM API to query elements
    // One very fast query is: document.getElementById
    // the document object represents the actual entry point into the DOM API
    
    // We query and store two elements so that we don't have to re-query each time WE WANT TO USE IT 
    var myHeaderElement = document.getElementById("header");
    var contentAreaElement = document.getElementById("content");
    
    // We can also create an element -- it won't appear until we add to it!
    // Let's create an unordered list
    var listOfDetails = document.createElement("ul");
    
    // We're going to use a timeout so that you can see the page before we add to it, then after
    
    // The setTimeout function takes 2 parameters: a function, and a number of milliseconds
    // it will run the function after the number of milliseconds provided
    // this is asynchronous! The code does not stop and wait for the timeout to occur
    console.log("Before the timeout");

    setTimeout(function () {
        console.log("In the timeout");
        
        // let's use the data in biographyPageOptions to update the page!
        // we can change the title easily; notice, it updates instantly
        document.title = biographyPageOptions.name;
        
        // For each element, we can manipulate them in many ways. 
        // One way is to set the entire content of the element with innerHTML, passing an HTML string
        myHeaderElement.innerHTML = "My name is " + biographyPageOptions.name;
        
        /*     var biographyPageOptions = {
        name: "Phil Barresi",
        hobby: "Making Coffee",
        favoriteVegetable: "Brussel Sprouts", // Seriously
        favoriteProgrammingLanguage: "JavaScript", // obviously
        currentProject: "w2p",
        currentProjectDescription: "w2p is a worker-to-promise library that will allow you to call functions on web workers, and use the results as promises!"
    };
    
    */
        // Let's create a list item to the unordered list for every detail
        
        var hobbyItem = document.createElement("li");
        hobbyItem.innerHTML = "My hobby is " + biographyPageOptions.hobby;
        listOfDetails.appendChild(hobbyItem);

        var veggie = document.createElement("li");
        veggie.innerHTML = "My favorite vegetable is " + biographyPageOptions.favoriteVegetable;
        listOfDetails.appendChild(veggie);

        var language = document.createElement("li");
        language.innerHTML = "My favorite language is " + biographyPageOptions.favoriteProgrammingLanguage;
        listOfDetails.appendChild(language);

        var currentProject = document.createElement("li");
        var descriptionText = document.createTextNode("I am currently working on a project");
        
        // We can add text as well!
        currentProject.appendChild(descriptionText);

        var subDetailsList = document.createElement("ul");

        var projectName = document.createElement("li");
        projectName.innerHTML = "I am working on a project called" + biographyPageOptions.currentProject;
        subDetailsList.appendChild(projectName);

        var projectDescription = document.createElement("li");
        projectDescription.innerHTML = biographyPageOptions.currentProjectDescription;
        subDetailsList.appendChild(projectDescription);
        
        // We can then add a new child, the whole list!
        currentProject.appendChild(subDetailsList);

        // and then add the whole current project element to the detail list
        listOfDetails.appendChild(currentProject);
        
        // Notice, it's still not on the page! Now let's append our 
        // list to the content area in another second and a half so we can notice that   
        setTimeout(function () {
            contentAreaElement.appendChild(listOfDetails)
        }, 1500);
    }, 3500);

    console.log("After the  timeout");

})();
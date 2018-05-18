(function($) {
    // Let's start writing AJAX calls!

    // example for AJAX
    /*
    $.ajax({
        method: "POST",
        url: "some.php",
        data: { name: "John", location: "Boston" }
    })
    .done(function( msg ) {
        alert( "Data Saved: " + msg );
    });*/

    // example for form

    /*
    $("#my-form").submit(function(e) {
        e.preventDefault();
         
    });
  */

    var myNewTaskForm = $("#new-item-form"),
        newNameInput = $("#new-task-name"),
        newDecriptionArea = $("#new-task-description");

    myNewTaskForm.submit(function(event) {
        event.preventDefault();

        var newName = newNameInput.val();
        var newDescription = newDecriptionArea.val();
        var newContent = $("#new-content");

        if (newName && newDescription) {
            var requestConfig = {
                method: "POST",
                url: "/api/todo",
                contentType: 'application/json',
                data: JSON.stringify({
                    name: newName,
                    description: newDescription,
                    testField: 12,
                    testBool: true
                })
            };
            
            $.ajax(requestConfig).then(function(responseMessage) {
                console.log(responseMessage);
                newContent.html(responseMessage.message);
                //                alert("Data Saved: " + msg);
            });
        }
    });
})(window.jQuery);
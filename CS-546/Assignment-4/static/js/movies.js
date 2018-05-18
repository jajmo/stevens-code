(function ($) {
   
    /*
     * Upvote a movie
     */
    $(document).on("click", ".upvote", function (e) {
        var movie = JSON.parse($(this).attr("data-movie"));
        modifyMovie (movie, true);
    });

    /*
     * Downvote a movie
     */
    $(document).on("click", ".downvote", function (e) {
        var movie = JSON.parse($(this).attr("data-movie"));
        modifyMovie (movie, false);
    });

    /**
     * Generic function to up/downvote a movie
     */
    function modifyMovie (movie, up) {
        // Get variables
        var id = movie['_id'];
        var currRating = parseInt(movie['rating']);
        var title = movie['title'];

        // Error check
        if (!id || (!currRating && currRating !== 0) || !title) {
            return;
        }

        // Determine the new rating
        var newRating = (up) ? currRating + 1 : currRating - 1;

        if (newRating > 5) {
            newRating = 5;
        } else if (newRating < 0) {
            newRating = 0;
        }

        // Build the query
        var request = {
            method: "PUT",
            url: "/api/movies/" + id,
            contentType: "application/json",
            data: JSON.stringify({
                title: title,
                rating: newRating
            })
        };

        // Send the request and update things accordingly
        $.ajax(request).then(function (response) {
            if (response['error']) {
                alert(response['error']);
            } else {
                $("#rating-" + id).html(newRating);
                $(".modify-" + id).attr("data-movie", "{ \"_id\": \"" + id + "\", \"title\": \"" + title + "\", \"rating\": \"" + newRating + "\"}");
            }
        });
    }

    /*
     * Delete a movie
     */
    $(document).on("click", ".delete", function (e) {
        var movieId = $(this).attr("data-id");

        if (!movieId) {
            return;
        }

        var userConfirmation = confirm("Do you wish to delete this movie?");

        if (!userConfirmation) {
            return;
        }

        // Delete the movie
        var request = {
            method: "DELETE",
            url: "/api/movies/" + movieId,
            contentType: "application/json"
        }

        $.ajax(request).then(function (response) {
            if (response['success'] == true) {
                // Slide up element and remove it from the DOM
                $("#" + movieId).slideUp("normal", function () { $(this).remove(); });
            } else {
                alert("Invalid movie ID!");
            }
        });
    });

    /*
     * Create a new movie
     */
    $("#submit-movie").on('click', function (e) {
        e.preventDefault();

        var title = $("#title").val();
        var rating = parseInt($("#rating").val());

        if (!title) {
            alert("Invalid title");
            return;
        }

        if (!rating || rating < 0 || rating > 5) {
            alert("Invalid rating");
            return;
        }

        var request = {
            method: "POST",
            url: "/api/movies",
            contentType: "application/json",
            data: JSON.stringify({
                title: title,
                rating: rating
            })
        };

        $.ajax(request).then(function (response) {
            if (response['error']) {
                alert(response['error']);
            } else {
                var request = {
                    method: "GET",
                    url: "/api/movies/" + response._id,
                    contentType: "application/json"
                };

                $.ajax(request).then(function (response) {
                    // Clear form and append to movie container
                    $("#title, #rating").val("");
                    $(response).appendTo("#movie-container").hide().slideDown();
                });
            }
        });
    });

    $("#popular-movies").on('click', function (e) {
        var request = {
            method: "GET",
            url: "/api/movies/best",
            contentType: "application/json"
        };

        $.ajax(request).then(function (response) {
            $("#movie-container").slideUp("normal", function () { 
                $(this).empty();
                $(response).appendTo($(this));
                $(this).slideDown();
            });
        });
    });

    $("#all-movies").on('click', function (e) {
        var request = {
            method: "GET",
            url: "/api/movies/all",
            contentType: "application/json"
        };

        $.ajax(request).then(function (response) {
            $("#movie-container").slideUp("normal", function () { 
                $(this).empty();
                $(response).appendTo($(this));
                $(this).slideDown();
            });
        });
    });
})(window.jQuery);
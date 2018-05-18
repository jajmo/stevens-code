(function ($) {
    
    $(document).on('click', "#previous-month", function (e) {
        getNewMonth(false);
    });

    $(document).on('click', "#next-month", function (e) {
        getNewMonth(true);
    });

    $(document).on('click', '#previous-day', function (e) {
        getNewDay(false);
    });

    $(document).on('click', '#next-day', function (e) {
        getNewDay(true);
    });

    $(document).on('click', '.add-event-btn', function (e) {
        $(".daily-view").fadeTo(400, 0.3);

        if ($(".calendar").is(":visible") || $(".footer-daily").is(":visible")) {
             $(".calendar, .row").fadeTo(400, 0.3);
             $(".footer-daily").fadeTo(400, 0.3);
        } else {
            $(".monthly-mobile").fadeTo(400, 0.3);
            $(".footer-mobile").fadeTo(400, 0.3);
        }
       
        $("#new-event-modal").fadeIn();
    });

    $(document).on('click', '.close, .home-btn', function (e) {
        $("#new-event-modal").fadeOut();
        $(".daily-view").fadeTo(400, 1);

        if ($(".calendar").is(":visible") || $(".footer-daily").is(":visible")) {
            $(".calendar, .row").fadeTo(400, 1);
            $(".footer-daily").fadeTo(400, 1);
        } else {
            $(".monthly-mobile").fadeTo(400, 1);
            $(".footer-mobile").fadeTo(400, 1);
        }
    });

    $(document).on('click', '#next-week', function (e) {
        getNewWeek(true);
    });

    $(document).on('click', '#previous-week', function (e) {
        getNewWeek(false);
    });

    $(document).keydown(function (e) {
        switch(e.which) {
            case 37: // Left key
                e.preventDefault();
                $("#previous-month").trigger('click');
                if ($(".footer-daily").is(":visible") || $(".calendar").is(":visible")) {
                    $("#previous-week").trigger('click');
                } else {
                    $("#previous-day").trigger('click');
                }
                break;
            case 39: // Right key
                e.preventDefault();
                $("#next-month").trigger('click');
                if ($(".footer-daily").is(":visible") || $(".calendar").is(":visible")) {
                    $("#next-week").trigger('click');
                } else {
                    $("#next-day").trigger('click');
                }
                break;
            case 27: // Escape key
                e.preventDefault();
                $(".close").trigger('click');
            default:
                return;
        }
    });

    $(document).on('click', '.home', function (e) {
        var info = $('h1').first().text().split(', ')[1].split(' ');
        var month = info[0];
        var year = info[2];
        window.location.href = "/monthnum/" + month + "/" + year;
    });

    $(document).on('click', '.home-task', function (e) {
        var info = $('h2').first().text().split(', ');
        var month = info[0].split(' ')[0];
        var year = info[1];

        window.location.href = "/monthnum/" + month + "/" + year;
    });

    $(document).on('click', '.delete', function (e) {
        var task = $('h1').first().text().trim();
        var info = $('h2').first().text().split(', ');
        var month = info[0].split(' ')[0];
        var day = info[0].split(' ')[1];
        var year = info[1];

        var request = {
            method: "GET",
            url: "/event/delete/" + year + "/" + month + "/" + day + "/" + task
        }

        $.ajax(request).then(function (res) {
            window.location.href = res.url;
        }); 
    });

    $(document).on('click', '.day', function (e) {
        var monthYear = $(".month-year").text().split(', ');
        var month = monthYear[0];
        var year = monthYear[1];
        var day = $(this).data('day');

        window.location.href = "/view/" + year + "/" + month + "/" + day;
    });

    $(document).on('click', '.slider-day', function (e) {
        var date = $(this).data('date').split('/');

        var request = {
            method: "GET",
            url: "/view/" + date[2] + "/" + (parseInt(date[0]) + 1) + "/" + date[1]
        };

        $.ajax(request).then(function (response) {
            $(".daily-view").html($(response).find(".daily-view").html());
            $(".footer-daily").html($(response).find(".footer-daily").html());
            $("#new-event-modal").html($(response).find("#new-event-modal").html());
        });
    });

    $(document).on('submit', '#new-task-form', function (e) {
        e.preventDefault();
        var title = $(this).find('[name=title]').val().trim();
        var location = $(this).find('[name=location]').val().trim();
        var description = $(this).find('[name=description]').val().trim();
        var month = $(this).find('[name=month]').val();
        var year = $(this).find('[name=year]').val();
        var day = $(this).find('[name=day]').val();

        if (!title) {
            $("#error").text("At least 'Title' is required");
            return;
        } else {
            $("#error").text("");
        }

        var page = (window.location.href.indexOf("view") > -1) ? "daily" : "monthly";

        var request = {
            method: "POST",
            url: "/events/create",
            contentType: "application/json",
            data: JSON.stringify({
                month: month,
                year: year,
                day: day,
                title: title,
                location: location,
                description: description,
                page: page
            })
        };

        $.ajax(request).then(function (response) {
            if (page == "monthly") {
                $(".calendar").html($(response).find(".calendar").html());
                $(".monthly-mobile").html($(response).find(".monthly-mobile").html());
            } else {
                $(".daily-view").html($(response).find(".daily-view").html());
            }
            
            $(".close").trigger("click");
            $("#new-task-form").find("input[type=text]").val("");
        });
    });

    function getNewWeek(next) {
        var date = $(".slider-day").last().data('date').split('/');
        var curr = new Date(parseInt(date[2]), parseInt(date[0]), parseInt(date[1]));

        if (next) {
            curr.setDate(curr.getDate() + 4);
        } else {
            curr.setDate(curr.getDate() - 10);
        }

        var request = {
            method: "GET",
            url: "/view/" + curr.getFullYear() + "/" + (curr.getMonth() + 1) + "/" + curr.getDate()
        };

        $.ajax(request).then(function (response) {
            $(".daily-view").html($(response).find(".daily-view").html());
            $(".footer-daily").html($(response).find(".footer-daily").html());
            $("#new-event-modal").html($(response).find("#new-event-modal").html());
        });
    }

    function getNewMonth(next) {
        var curr_date = $(".month-year").text().split(", ");
        var month_num = parseInt((new Date(curr_date[0] + " " + curr_date[1])).getMonth());
        month_num = (next) ? month_num += 1 : month_num -= 1;

        if (!next && month_num == -1) {
            // Wrap around to the previous year
            month_num = 11;
            curr_date[2]--;
        } else if (next && month_num == 12) {
            // Wrap around to the next year
            month_num = 0;
            curr_date[2]++;
        }

        var request = {
            method: "GET",
            url: "/" + month_num + "/" + curr_date[2]
        }

        $.ajax(request).then(function (response) {
            // Replace the calendar and month/year
            $(".calendar").html($(response).find(".calendar").html());
            $("#new-event-modal").html($(response).find("#new-event-modal").html())
            $(".month-year").html($(response).find(".month-year").html());
            $(".monthly-mobile").html($(response).find(".monthly-mobile").html());
        });
    }

    function getNewDay(next) {
        var curr_date = $(".footer-mobile").find("p").text().split('/');
        var d = new Date(parseInt(curr_date[2]), parseInt(curr_date[0]), parseInt(curr_date[1]));

        if (next) {
            d.setDate(d.getDate() + 1);
        } else {
            d.setDate(d.getDate() - 1);
        }

        var request = {
            method: "GET",
            url: "/view/" + d.getFullYear() + "/" + d.getMonth() + "/" + d.getDate()
        }

        $.ajax(request).then(function (response) {
            $(".daily-view").html($(response).find(".daily-view").html());
            $(".footer-daily").html($(response).find(".footer-daily").html());
            $(".footer-mobile").html($(response).find(".footer-mobile").html());
        });
    }

})(window.jQuery);
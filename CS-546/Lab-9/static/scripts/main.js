(function($) {
    $("nav a").on("click", function(event) {
        var anchor = $(this);

        var target = anchor.attr("href");
        var chapterTarget = $(target);

        $(".chapter.active").removeClass("active");
        chapterTarget.addClass("active");   
    })
})(jQuery);
const gulp = require("gulp");
const gulpWatch = require("gulp");
const concatenate = require("gulp-concat");
const cleanCSS = require("gulp-clean-css");
const autoPrefix = require("gulp-autoprefixer");
const gulpSASS = require("gulp-sass");
const rename = require("gulp-rename");
const uglify = require("gulp-uglify");
const clean = require("gulp-clean");

// Source files
const sassFiles = "./public/css/source/sass/**/*.scss";
const jsFiles = "./public/js/*.js";

// Files that will be cleaned
const cleanCSSFiles = ["./dist/css/*.css"];
const cleanJSFiles = ["./dist/js/*.js", "./public/js/scripts.js"];

gulp.task("cleanCSS", () => {
    return gulp.src(cleanCSSFiles)
               .pipe(clean());
});

gulp.task("cleanJS", () => {
    return gulp.src(cleanJSFiles)
               .pipe(clean());
});

gulp.task("sass", ["cleanCSS"], () => {
    gulp.src(sassFiles)
        .pipe(gulpSASS())
        .pipe(concatenate("styles.min.css"))
        .pipe(autoPrefix())
        .pipe(cleanCSS())
        .pipe(gulp.dest("./dist/css/"));
});

gulp.task("js", ["cleanJS"], () => {
    gulp.src(jsFiles)
        .pipe(concatenate('scripts.js'))
        .pipe(gulp.dest("./public/js"))
        .pipe(rename("calendar.min.js"))
        .pipe(uglify())
        .pipe(gulp.dest("./dist/js"));
});

gulp.task("watch", () => {
    gulp.watch(sassFiles, ["sass"]);
    gulp.watch(jsFiles, ["js"]);
});

gulp.task("default", ["watch"]);

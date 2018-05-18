(function ($, document) {
    // Form objects
    var retirementSavingsForm = $("#retirement-savings");
    var investmentForm = $("#investment");
    var loanPayoffForm = $("#loan-payoff");

    // Submit handler for retirementSavingsForm
    retirementSavingsForm.submit(function (event) {
        var err = [];
        var years = parseInt($("#years").val());
        var monthlyAmount = parseInt($("#perMonth").val());
        var interestRate = parseInt($("#interestRate").val());

        if (isNaN(years) || years < 1) {
            err.push('Years must be a number greater than 0');
        }

        if (isNaN(monthlyAmount) || monthlyAmount < 1) {
            err.push('Monthly amount must be a number greater than 0');
        }

        if (isNaN(interestRate) || interestRate < 0 || interestRate > 1) {
            err.push('Interest rate must be a number between 0 and 1');
        }

        handleErrors(retirementSavingsForm, err, event);
    });

    // Submit handler for investmentForm
    investmentForm.submit(function (event) {
        var err = [];
        var years = parseInt($("#investYears").val());
        var initialInvestment = parseInt($("#initial").val());
        var interestRate = parseInt($("#investedInterestRate").val());

        if (isNaN(years) || years < 1) {
            err.push('Years must be a number greater than 0');
        }

        if (isNaN(initialInvestment) || initialInvestment < 1) {
            err.push('Initial investment must be a number greater than 0');
        }

        if (isNaN(interestRate) || interestRate < 0 || interestRate > 1) {
            err.push('Interest rate must be a number between 0 and 1');
        }

        handleErrors(investmentForm, err, event);
    });

    // Submit handler for the loan payoff form
    loanPayoffForm.submit(function (event) {
        var err = [];
        var monthlyAmount = parseInt($("#monthlyAmount").val());
        var loanAmount = parseInt($("#loanAmount").val());
        var interestRate = parseInt($("#loanInterestRate").val());

        if (isNaN(monthlyAmount) || monthlyAmount < 1) {
            err.push('Monthly amount must be a number greater than 0');
        }

        if (isNaN(loanAmount) || loanAmount < 1) {
            err.push('Loan amount must be a number greater than 0');
        }

        if (isNaN(interestRate) || interestRate < 0 || interestRate > 1) {
            err.push('Interest rate must be a number between 0 and 1');
        }

        handleErrors(loanPayoffForm, err, event);
    });

    // Handle errors from the submit handlers
    function handleErrors (form, errorArray, event) {
        if (errorArray.length > 0) { // We only want to handle errors if there's errors in the array
            var formErrorObject = form.find("#error-message");
            // Clear out old errors
            formErrorObject.empty();

            // Create a new <ul>
            var list = document.createElement('ul');

            // Iterate over errors
            errorArray.forEach(function (elem) {
                // For each error, create a new <li> and append it to the parent <ul>
                var error = document.createElement('li');
                error.innerHTML = elem;
                list.appendChild(error);
            });

            // Append the <ul> to the form error object, unhide it, and prevent the form from submitting
            formErrorObject.append(list);
            formErrorObject.removeClass('hidden');
            event.preventDefault();
        }
    }
})(jQuery, document);
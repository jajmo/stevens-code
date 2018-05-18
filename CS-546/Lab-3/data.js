var exports = module.exports = {};

/**
 * retirementAmountIfSavingPerMonth()
 *
 * Calculate the amount of money that will be saved based on saving on a monthly basis
 *
 * @param number yearsUntilRetirement The number of years until retirement
 * @param number amountSavingPerMonth The amount of money being saved per month
 * @param number yearlyInterestRateOfInvestment The yearly interest rate of the investment
 */
exports.retirementAmountIfSavingPerMonth = function (yearsUntilRetirement, amountSavingPerMonth, yearlyInterestRateOfInvestment) {
    var total = 0;

    // Make sure everything is a number and >= 0
    if (typeof yearsUntilRetirement != "number" || typeof amountSavingPerMonth != "number" || typeof yearsUntilRetirement != "number" ||
        yearsUntilRetirement < 0 || amountSavingPerMonth < 0 || yearlyInterestRateOfInvestment < 0 ||
        isNaN(yearsUntilRetirement) || isNaN(amountSavingPerMonth) || isNaN(yearlyInterestRateOfInvestment)) {
        throw "Invalid arguments";
    }

    // Calculate running total
    for (var i = 0; i < yearsUntilRetirement; i++) {
        total = (total + amountSavingPerMonth) * (1 + (yearlyInterestRateOfInvestment / 12));
    }

    // We only care about two decimal places
    return total.toFixed(2);
}

/**
 * investedAmountAfterSomeYears()
 *
 * Calculate the end amount of money after investing for a certain number of years at a fixed interest rate
 *
 * @param number yearsInvesting The number of years to invest for
 * @param number initialAmount The starting amount of money
 * @param number yearlyInterestRateOfInvestment The amount of interest earned per year
 */
exports.investedAmountAfterSomeYears = function (yearsInvesting, initialAmount, yearlyInterestRateOfInvestment) {
    var total = initialAmount;

    // Make sure everyting is a number and >= 0
    if (typeof yearsInvesting != "number" || typeof initialAmount != "number" || typeof yearlyInterestRateOfInvestment != "number" ||
        yearsInvesting < 0 || initialAmount < 0 || yearlyInterestRateOfInvestment < 0 ||
        isNaN(yearsInvesting) || isNaN(initialAmount) || isNaN(yearlyInterestRateOfInvestment)) {
        throw "Invalid arguments";
    }

    // Calculate running total
    for (var i = 0; i < yearsInvesting; i++) {
        total = total * (1 + yearlyInterestRateOfInvestment);
    }

    // We only care about two decimal places
    return total.toFixed(2);
}

/**
 * monthsToPayOffLoan()
 *
 * Calculate how many months are required to pay off a loan
 *
 * @param number monthlyPaymentAmount The amount being paid off per month
 * @param number initialLoanAmount The amount of the initial loan
 * @param number yearlyInterestRateOfLoan The yearly interest rate of the loan
 */
exports.monthsToPayOffLoan = function (monthlyPaymentAmount, initialLoanAmount, yearlyInterestRateOfLoan) {
    var months = 0;

    // Make sure everything is a number and >= 0
    if (typeof monthlyPaymentAmount != "number" || typeof initialLoanAmount != "number" || typeof yearlyInterestRateOfLoan != "number" ||
        monthlyPaymentAmount < 0 || initialLoanAmount < 0 || yearlyInterestRateOfLoan < 0 ||
        isNaN(monthlyPaymentAmount) || isNaN(initialLoanAmount) || isNaN(yearlyInterestRateOfLoan)) {
        throw "Invalid arguments";
    }

    // Calculate months
    while (initialLoanAmount > 0) {
        initialLoanAmount = (initialLoanAmount * (1 + (yearlyInterestRateOfLoan / 12))) - monthlyPaymentAmount;
        months++;
    }

    return months;
}

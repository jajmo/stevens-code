import java.util.ArrayList;
import java.util.List;

public class PrimeFinder implements Runnable {
	private Integer start;
	private Integer end;
	private List<Integer> primes;
	
	PrimeFinder(Integer startNum, Integer endNum) {
		if (startNum < 2) {
			startNum = 2;
		}

		this.start = startNum;
		this.end = endNum;
		this.primes = new ArrayList<Integer>();
	}
	
	public Boolean isPrime(int n) {
		for(int i = 2; i < n; i++) {
			if (n % i == 0) {
				return false;
			}
		}
		
		return true;
	}
	
	public List<Integer> getPrimesList() {
		return this.primes;
	}

	public void run() {
		for(int i = start; i < end; i++) {
			if (isPrime(i)) {
				primes.add(i);
			}
		}
	}
}

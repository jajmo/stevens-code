import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AssignmentOne {
	private List<Integer> results;
	
	AssignmentOne() {
		results = new ArrayList<Integer>();
	}
	
	public List<Integer> lprimes(List<Integer[]> intervals) {
		Map<Thread, PrimeFinder> threads = new HashMap<Thread, PrimeFinder>();
		PrimeFinder pt;
		
		// Create and run threads
		for(Integer[] interval : intervals) {
			if (interval.length < 2) {
				// Invalid length
				continue;
			}
			
			pt = new PrimeFinder(interval[0], interval[1]);
			Thread t = new Thread(pt);
			threads.put(t, pt);
			t.start();
		}
		
		// Wait for all threads to finish
		for(Thread t : threads.keySet()) {
			try {
				t.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		// Collect results
		for(Thread t : threads.keySet()) {
			results.addAll(threads.get(t).getPrimesList());
		}
		
		Collections.sort(results);
		return results;
	}
	
	public static void main(String[] args) {
		List<Integer[]> input = new ArrayList<Integer[]>();
		
		for(int i = 0; i < args.length - 1; i++) {
			input.add(new Integer[]{ Integer.parseInt(args[i]), Integer.parseInt(args[i + 1]) });
		}
		
		System.out.println(new AssignmentOne().lprimes(input));
	}
}

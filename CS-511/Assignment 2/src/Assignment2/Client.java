package Assignment2;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ThreadLocalRandom;
import Assignment2.WeightPlate.WeightPlateSize;

public class Client implements Runnable {
	// Max of 15 exercises
	private static final int MAX_ROUTINE_SIZE = 15;
	private int id;
	private List<Exercise> routine;
	
	public Client(int id) {
		this.id = id;
		this.routine = new ArrayList<Exercise>();
	}
	
	public Client() {
		this.routine = new ArrayList<Exercise>();
	}
	
	public void addExercise(Exercise e) {
		routine.add(e);
	}
	
	public static Client generateRandom(int id) {
		Client c = new Client(id);
		int numExercises = ThreadLocalRandom.current().nextInt(1, MAX_ROUTINE_SIZE + 1);
		
		for (int i = 0; i < numExercises; i++) {
			c.addExercise(Exercise.generateRandom());
		}
		
		return c;
	}

	public void run() {
		int i;

		for (Exercise e : routine) {
			try {
				// First, acquire apparatus
				Gym.apparatusSems.get(e.getApparatus()).acquire();
				System.out.println("[" + id + "] has acquired a " + Apparatus.strings.get(e.getApparatus()));
				
				// Second, acquire weight semaphores
				Gym.acquireWeights.acquire();
					for(Map.Entry<WeightPlateSize, Integer> weight : e.getWeight().entrySet()) {
						for(i = 0; i < weight.getValue(); i++) {
							Gym.weightSems.get(weight.getKey()).acquire();
						}
						
						System.out.println("[" + id + "] has acquired " + weight.getValue() + " " + WeightPlate.strings.get(weight.getKey()) + " weights");
					}
				Gym.acquireWeights.release();

				System.out.println("[" + id + "] is performing exercises.");
	
				// Perform the exercise
				Thread.sleep((long) (e.getDuration() * 1000));
				
				/**
				 * Release apparatus and equipment
				 */
				for(Map.Entry<WeightPlateSize, Integer> weight : e.getWeight().entrySet()) {
					for(i = 0; i < weight.getValue(); i++) {
						Gym.weightSems.get(weight.getKey()).release();
					}
				}
				Gym.apparatusSems.get(e.getApparatus()).release();
				System.out.println("[" + id + "] has released a " + Apparatus.strings.get(e.getApparatus()));
			} catch(InterruptedException e1) {
				e1.printStackTrace();
			}
		}
	}
}

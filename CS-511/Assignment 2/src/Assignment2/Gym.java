package Assignment2;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;
import Assignment2.Apparatus.ApparatusType;
import Assignment2.WeightPlate.WeightPlateSize;

public class Gym implements Runnable {
	// Semaphores for accessing equipment
	public static Semaphore acquireWeights = new Semaphore(1);
	public static Map<WeightPlateSize, Semaphore> weightSems = new HashMap<WeightPlateSize, Semaphore>();
	public static Map<ApparatusType, Semaphore> apparatusSems = new HashMap<ApparatusType, Semaphore>();
	
	// Local variables
	private static final int GYM_SIZE = 30;
	private static final int GYM_REGISTERED_CLIENTS = 10000;
	private static final int NUM_APPARATUS = 5; // How many of each apparatus does the gym have?
	private Map<WeightPlateSize, Integer> noOfWeightPlates;
	private Set<Integer> clients;
	private ExecutorService executor;
	
	public Gym() {
		noOfWeightPlates = new HashMap<WeightPlateSize, Integer>();
		clients = new HashSet<Integer>();
		
		// Populate string maps
		WeightPlate.populateMap();
		Apparatus.populateMap();
		
		// Set number of weights
		noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, 40);
		noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, 30);
		noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, 20);
		
		// Create weight plate semaphores
		weightSems.put(WeightPlateSize.SMALL_3KG, new Semaphore(noOfWeightPlates.get(WeightPlateSize.SMALL_3KG)));
		weightSems.put(WeightPlateSize.MEDIUM_5KG, new Semaphore(noOfWeightPlates.get(WeightPlateSize.MEDIUM_5KG)));
		weightSems.put(WeightPlateSize.LARGE_10KG, new Semaphore(noOfWeightPlates.get(WeightPlateSize.LARGE_10KG)));
		
		// Create apparatus semaphores
		for(ApparatusType a : Apparatus.ApparatusType.values()) {
			apparatusSems.put(a, new Semaphore(NUM_APPARATUS));
		}
	}
	
	public void run() {
		int i, id;
		
		executor = Executors.newFixedThreadPool(GYM_SIZE);

		for (i = 0; i < GYM_REGISTERED_CLIENTS; i++) {
			id = ThreadLocalRandom.current().nextInt(1, GYM_REGISTERED_CLIENTS + 1);
			clients.add(id);
			executor.execute(Client.generateRandom(id));
		}
		
		executor.shutdown();
	}
}

package Assignment2;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ThreadLocalRandom;
import Assignment2.Apparatus.ApparatusType;
import Assignment2.WeightPlate.WeightPlateSize;

public class Exercise {
	 private ApparatusType at;
	 private Map<WeightPlateSize, Integer> weight;
	 private double duration; // In milliseconds
	 
	 public void Routine(ApparatusType at, Map<WeightPlateSize, Integer> weight) {
		 this.at = at;
		 this.weight = weight;
		 this.duration = Math.random() % 0.2; // Cap duration at 0.2 to make the simulation shorter
	 }
	 
	 public double getDuration() {
		 return this.duration;
	 }
	 
	 public Map<WeightPlateSize, Integer> getWeight() {
		 return weight;
	 }
	 
	 public ApparatusType getApparatus() {
		 return at;
	 }
	 
	 public static Exercise generateRandom() {
		 Exercise e = new Exercise();
		 Map<WeightPlateSize, Integer> weights = new HashMap<WeightPlateSize, Integer>();
		 ApparatusType a = Apparatus.ApparatusType.getRandom();
		 
		 // Generate a random number of each weight size
		 int smallWeight = ThreadLocalRandom.current().nextInt(1, WeightPlate.MAX_WEIGHT_PLATE_AMOUNT + 1);
		 int medWeight = ThreadLocalRandom.current().nextInt(1, WeightPlate.MAX_WEIGHT_PLATE_AMOUNT + 1);
		 int lgWeight = ThreadLocalRandom.current().nextInt(1, WeightPlate.MAX_WEIGHT_PLATE_AMOUNT + 1);
		 
		 weights.put(WeightPlateSize.SMALL_3KG, smallWeight);
		 weights.put(WeightPlateSize.MEDIUM_5KG, medWeight);
		 weights.put(WeightPlateSize.LARGE_10KG, lgWeight);
		 e.Routine(a, weights);
		 
		 return e;
	 }
}

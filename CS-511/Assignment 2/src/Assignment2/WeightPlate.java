package Assignment2;

import java.util.HashMap;
import java.util.Map;

public class WeightPlate {

	// Max of 10 weight plates per size
	public static final int MAX_WEIGHT_PLATE_AMOUNT = 10;
	public static Map<WeightPlateSize, String> strings = new HashMap<WeightPlateSize, String>();
	
	public static void populateMap() {
		strings.put(WeightPlateSize.SMALL_3KG, "small");
		strings.put(WeightPlateSize.MEDIUM_5KG, "medium");
		strings.put(WeightPlateSize.LARGE_10KG, "large");
	}

	public enum WeightPlateSize {
		 SMALL_3KG, MEDIUM_5KG, LARGE_10KG;
	 };
}

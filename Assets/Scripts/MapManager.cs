using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapManager : MonoBehaviour {
    public static MapManager Instance;

    public int width;
    public int height;

	// Use this for initialization
	void Awake () {
        if (Instance == null) Instance = this;
	}

    // Update is called once per frame
    void Update () {
		
	}
}

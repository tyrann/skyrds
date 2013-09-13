using UnityEngine;
using System.Collections;

public class Finish : MonoBehaviour {

	void OnTriggerEnter (Collider other) {
		if (other.CompareTag("Player")) {
			other.transform.position = GameObject.FindGameObjectWithTag("Respawn").transform.position;
		}
	}
}

import React, { Component } from 'react';
import LightToggle from './LightToggle';
import FanToggle from './FanToggle';

import API from '../Api';

export default class MainPage extends Component {
	constructor(props) {
		super(props);
		this.state = {
			temp: '',
			hum: '',
			light1: [],
			light2: [],
			light3: [],
			isLoaded: false
		};
		this.getLightsValues();
	}

	componentWillMount() {
		this.getLightsValues();
	}

	componentDidMount() {
		this.startAutoUpdate();
	}

	async startAutoUpdate() {
		this.autoUpdateSensors = setInterval(async () => {
			const res = await API.get('/sensors');
			const { sensors } = res.data;
			this.setState({ temp: sensors[0].value });
			this.setState({ hum: sensors[1].value });
		}, 1 * 1000);
	}

	async getLightsValues() {
		const res = await API.get('/lights');
		const { lights } = res.data;
		this.setState({ light1: lights[0] });
		this.setState({ light2: lights[1] });
		this.setState({ light3: lights[2] });
		this.setState({ isLoaded: true });
	}

	render() {
		// Éléments visuels sans component:
		// - la température
		// - le pourcentage

		// Component global pour changer les couleurs
		//  Component pour changer la couleur blanche
		//  Component pour changer la couleur rouge
		//  Component pour changer la couleur bleue

		// Component global pour changer les fans
		//  Component pour changer la fan 1
		//  Component pour changer la fan 2

		return (
			<div className="main-page">
				<div className="title">Tableau de bord</div>
				<div className="components">	
					<div className="first-section">
						<p id="temperature">{this.state.temp}</p>
						{this.state.isLoaded &&
							<div className="colors">
								<LightToggle light={this.state.light1} id={1} />
								<LightToggle light={this.state.light2} id={2} />
								<LightToggle light={this.state.light3} id={3} />
							</div>
						}
					</div>
					<div className="second-section">
						<p id="percentage">{this.state.hum}</p>
						<div className="fans">
							<FanToggle name="Fan1" id={1} />
							<FanToggle name="Fan2" id={2} />
						</div>
					</div>
				</div>
			</div>
		);
	}
}

import React, { Component } from 'react';
import LightToggle from './LightToggle';
import FanToggle from './FanToggle';
import _ from 'lodash';
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
			fanl: {},
			fanh: {},
			lightsLoaded: false,
			fansLoaded: false
		};
	}

	async componentWillMount() {
		await this.getLightsValues();
		await this.getFansValues();
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

	async getFansValues() {
		const { data } = await API.get('/fans');
		this.setState({
			fanl: data.fans[0],
			fanh: data.fans[1],
			fansLoaded: true
		});
	}

	async getLightsValues() {
		const { data } = await API.get('/lights');
		const { lights } = data;
		this.setState({
			light1: lights[0],
			light2: lights[1],
			light3: lights[2],
			lightsLoaded: true
		});
	}

	render() {
		// Éléments visuels sans component:
		// - la température
		// - le pourcentage

		//  Component pour changer la couleur blanche
		//  Component pour changer la couleur rouge
		//  Component pour changer la couleur bleue

		//  Component pour changer la fan 1
		//  Component pour changer la fan 2

		return (
			<div className="main-page">
				<div className="title">Tableau de bord</div>
				<div className="components">
					<div className="first-section">
						<p id="temperature">{this.state.temp}</p>
						{this.state.lightsLoaded &&
							<div className="colors">
								<LightToggle
									changeValue={async (value) => {
										const { light1 } = this.state;
										this.setState({ light1: { ...light1, value } });
										await API.post('/lights', {
											red: value,
											blue: this.state.light2.value,
											white: this.state.light3.value
										}, { headers: { 'Content-Type': 'application/json' } });
									}}
									light={this.state.light1}
									id={1}
								/>
								<LightToggle
									changeValue={async (value) => {
										const { light2 } = this.state;
										this.setState({ light2: { ...light2, value } });
										await API.post('/lights', {
											red: this.state.light1.value,
											blue: value,
											white: this.state.light3.value
										}, { headers: { 'Content-Type': 'application/json' } });
									}}
									light={this.state.light2}
									id={2}
								/>
								<LightToggle
									changeValue={async (value) => {
										const { light3 } = this.state;
										this.setState({ light3: { ...light3, value } });
										await API.post('/lights', {
											red: this.state.light1.value,
											blue: this.state.light2.value,
											white: value
										}, { headers: { 'Content-Type': 'application/json' } });
									}}
									light={this.state.light3}
									id={3}
								/>
							</div>
						}
					</div>
					<div className="second-section">
						<p id="percentage">{this.state.hum}</p>
						{this.state.fansLoaded &&
							<div className="fans">
								<FanToggle
									fan={this.state.fanh}
									id={1}
									handleChange={async (checked) => {
										const { fanh } = this.state,
											value = checked ? 255 : 0;
										this.setState({
											fanh: { ...fanh, value }
										});
										await API.post('/fans', {
											fanh: value,
											fanl: parseInt(this.state.fanl.value)
										}, { headers: { 'Content-Type': 'application/json' } });
									}}
								/>
								<FanToggle
									fan={this.state.fanl}
									id={2}
									handleChange={async (checked) => {
										const { fanl } = this.state,
											value = checked ? 255 : 0;
										this.setState({
											fanl: { ...fanl, value }
										});
										await API.post('/fans', {
											fanl: value,
											fanh: parseInt(this.state.fanh.value)
										}, { headers: { 'Content-Type': 'application/json' } });
									}}
								/>
							</div>
						}
					</div>
				</div>
			</div>
		);
	}
}
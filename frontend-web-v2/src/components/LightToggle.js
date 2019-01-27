import React from 'react';
import Slider from 'rc-slider';
import API from '../Api';

export default class LightToggle extends React.Component {
	constructor(props) {
		super(props);

		// set state..
		this.state = {
			...props,
		}
	}

	render() {
		return (
			<div className="color">
				<div className="name">
					{this.state.light.name}
				</div>
				<div>
					<Slider
						max={255}
						value={parseInt(this.state.light.value)}
						onChange={this.handleLightChange}
						onAfterChange={this.handleLightAfterChange}
						className="slider"
						trackStyle={{
							backgroundColor: this.state.light.name.toLowerCase(),
						}}
						handleStyle={{
							border: `2px solid ${this.state.light.name.toLowerCase()}`
						}}
					/>
				</div>
			</div>
		)
	}

	handleLightAfterChange = async (value) => {
		const { blue, red, white } = this.state;
		await API.post('/lights', {
			blue: blue ? blue.value : value,
			red: red ? red.value : value,
			white: white ? white.value : value
		}, { headers: { 'Content-Type': 'application/json' } });
	}

	handleLightChange = (value) => {
		const { light } = this.state
		this.setState({ light: { ...light, value } });
	}
}

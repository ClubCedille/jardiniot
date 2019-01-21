import React from 'react';
import Slider from 'rc-slider';

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
						value={parseInt(this.state.light.value)} 
						max={255} 
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
}

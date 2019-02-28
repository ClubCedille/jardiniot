import React, { Component } from 'react';
import { Link } from 'react-router-dom';
import HamburgerMenu from 'react-hamburger-menu';
import Sidebar from 'react-sidebar';
import SidebarContent from './Sidebar';

class Header extends Component {
	constructor(props) {
		super(props);

		this.state = {
			isMenuOpen: false
		};
	}

	render() {
		return (
			<Sidebar
				sidebar={<SidebarContent onHamburgerClick={this.onHamburgerClick} parent={this} />}
				open={this.state.isMenuOpen}
				onSetOpen={this.onHamburgerClick.bind(this)}
				styles={{ sidebar: { background: "black" } }}
				pullRight={true}
			>
				<header>
					<div className="custom-container">
						<Link to="/">
							<img className="logo" src="/img/cedille-logo.png" />
						</Link>
						<div className="title">Jardiniot</div>
						<div className="menu">
							<HamburgerMenu
								isOpen={this.state.isMenuOpen}
								menuClicked={this.onHamburgerClick.bind(this)}
								width={25}
								height={22}
								strokeWidth={1}
								rotate={1}
								color="black"
								borderRadius={0}
								animationDuration={0.5}
							/>
						</div>
					</div>
				</header>
			</Sidebar>
		);
	}

	onHamburgerClick(e) {
		this.setState({
			isMenuOpen: !this.state.isMenuOpen
		});

		console.log('oui allo');
	}
}

export default Header;